bfa_ioc_send_enable(struct bfa_ioc_s *ioc)
{
	struct bfi_ioc_ctrl_req_s enable_req;
	struct timeval tv;

	bfi_h2i_set(enable_req.mh, BFI_MC_IOC, BFI_IOC_H2I_ENABLE_REQ,
		    bfa_ioc_portid(ioc));
	enable_req.clscode = cpu_to_be16(ioc->clscode);
	do_gettimeofday(&tv);
	enable_req.tv_sec = be32_to_cpu(tv.tv_sec);
	bfa_ioc_mbox_send(ioc, &enable_req, sizeof(struct bfi_ioc_ctrl_req_s));
}
