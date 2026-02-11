esp_init_swstate(struct esp *esp)
{
	int i;

	INIT_LIST_HEAD(&esp->queued_cmds);
	INIT_LIST_HEAD(&esp->active_cmds);
	INIT_LIST_HEAD(&esp->esp_cmd_pool);


	for (i = 0 ; i < ESP_MAX_TARGET; i++) {
		esp->target[i].flags = 0;
		esp->target[i].nego_goal_period = 0;
		esp->target[i].nego_goal_offset = 0;
		esp->target[i].nego_goal_width = 0;
		esp->target[i].nego_goal_tags = 0;
	}
}
