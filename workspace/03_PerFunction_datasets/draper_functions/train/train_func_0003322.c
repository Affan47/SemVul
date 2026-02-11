hpsa_send_reset(struct ctlr_info *h, unsigned char *scsi3addr,
	u8 reset_type, int reply_queue)
{
	int rc = IO_OK;
	struct CommandList *c;
	struct ErrorInfo *ei;

	c = cmd_alloc(h);


	(void) fill_cmd(c, reset_type, h, NULL, 0, 0,
			scsi3addr, TYPE_MSG);
	rc = hpsa_scsi_do_simple_cmd(h, c, reply_queue, NO_TIMEOUT);
	if (rc) {
		dev_warn(&h->pdev->dev, "Failed to send reset command\n");
		goto out;
	}


	ei = c->err_info;
	if (ei->CommandStatus != 0) {
		hpsa_scsi_interpret_error(h, c);
		rc = -1;
	}
out:
	cmd_free(h, c);
	return rc;
}
