try_mailbox(struct ivtv *itv, struct ivtv_mailbox_data *mbdata, int mb)
{
	u32 flags = readl(&mbdata->mbox[mb].flags);
	int is_free = flags == IVTV_MBOX_FREE || (flags & IVTV_MBOX_FIRMWARE_DONE);


	if (is_free && !test_and_set_bit(mb, &mbdata->busy)) {
		write_sync(IVTV_MBOX_DRIVER_BUSY, &mbdata->mbox[mb].flags);
		return 1;
	}
	return 0;
}
