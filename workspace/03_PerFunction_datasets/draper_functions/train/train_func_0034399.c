imap_refcounted_done_box( imap_store_t *ctx ATTR_UNUSED, struct imap_cmd *cmd, int response )
{
	struct imap_cmd_refcounted_state *sts = ((struct imap_cmd_refcounted *)cmd)->state;

	switch (response) {
	case RESP_CANCEL:
		sts->ret_val = DRV_CANCELED;
		break;
	case RESP_NO:
		if (sts->ret_val == DRV_OK)
			sts->ret_val = DRV_BOX_BAD;
		break;
	}
	imap_refcounted_done( sts );
}
