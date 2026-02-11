error_reset(struct cardstate *cs)
{

	update_basstate(cs->hw.bas, BS_RESETTING, 0);
	if (req_submit(cs->bcs, HD_RESET_INTERRUPT_PIPE, 0, BAS_TIMEOUT))

		usb_queue_reset_device(cs->hw.bas->interface);
}
