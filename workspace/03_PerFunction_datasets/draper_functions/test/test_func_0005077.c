bfa_ioim_start(struct bfa_ioim_s *ioim)
{
	bfa_ioim_cb_profile_start(ioim->fcpim, ioim);


	ioim->reqq = bfa_fcpim_ioredirect_enabled(ioim->bfa) ?
			BFA_FALSE : bfa_itnim_get_reqq(ioim);

	bfa_sm_send_event(ioim, BFA_IOIM_SM_START);
}
