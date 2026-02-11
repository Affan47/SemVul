esp_reset_cleanup(struct esp *esp)
{
	struct esp_cmd_entry *ent, *tmp;
	int i;

	list_for_each_entry_safe(ent, tmp, &esp->queued_cmds, list) {
		struct scsi_cmnd *cmd = ent->cmd;

		list_del(&ent->list);
		cmd->result = DID_RESET << 16;
		cmd->scsi_done(cmd);
		esp_put_ent(esp, ent);
	}

	list_for_each_entry_safe(ent, tmp, &esp->active_cmds, list) {
		if (ent == esp->active_cmd)
			esp->active_cmd = NULL;
		esp_reset_cleanup_one(esp, ent);
	}

	BUG_ON(esp->active_cmd != NULL);


	for (i = 0; i < ESP_MAX_TARGET; i++) {
		struct esp_target_data *tp = &esp->target[i];

		tp->esp_period = 0;
		tp->esp_offset = 0;
		tp->esp_config3 &= ~(ESP_CONFIG3_EWIDE |
				     ESP_CONFIG3_FSCSI |
				     ESP_CONFIG3_FAST);
		tp->flags &= ~ESP_TGT_WIDE;
		tp->flags |= ESP_TGT_CHECK_NEGO;

		if (tp->starget)
			__starget_for_each_device(tp->starget, NULL,
						  esp_clear_hold);
	}
	esp->flags &= ~ESP_FLAG_RESETTING;
}
