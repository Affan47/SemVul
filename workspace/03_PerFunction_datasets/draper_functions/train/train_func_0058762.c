asd_tmf_tasklet_complete(struct asd_ascb *ascb,
				     struct done_list_struct *dl)
{
	struct tasklet_completion_status *tcs;

	if (!del_timer(&ascb->timer))
		return;

	tcs = ascb->uldd_task;
	ASD_DPRINTK("tmf tasklet complete\n");

	tcs->dl_opcode = dl->opcode;

	if (dl->opcode == TC_SSP_RESP) {
		tcs->tmf_state = asd_get_tmf_resp_tasklet(ascb, dl);
		tcs->tag_valid = ascb->tag_valid;
		tcs->tag = ascb->tag;
	}

	complete(ascb->completion);
	asd_ascb_free(ascb);
}
