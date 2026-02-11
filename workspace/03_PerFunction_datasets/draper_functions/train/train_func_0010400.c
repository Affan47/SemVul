bfa_ioc_fwsync(struct bfa_ioc_s *ioc)
{
	u32 fwsync_iter = 1000;

	bfa_ioc_send_fwsync(ioc);


	while (bfa_ioc_mbox_cmd_pending(ioc) && fwsync_iter > 0)
		fwsync_iter--;
}
