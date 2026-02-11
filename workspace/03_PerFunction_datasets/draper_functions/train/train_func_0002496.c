bfa_ioc_sm_getattr(struct bfa_ioc_s *ioc, enum ioc_event event)
{
	bfa_trc(ioc, event);

	switch (event) {
	case IOC_E_FWRSP_GETATTR:
		bfa_ioc_timer_stop(ioc);
		bfa_fsm_set_state(ioc, bfa_ioc_sm_op);
		break;

	case IOC_E_PFFAILED:
	case IOC_E_HWERROR:
		bfa_ioc_timer_stop(ioc);

	case IOC_E_TIMEOUT:
		ioc->cbfn->enable_cbfn(ioc->bfa, BFA_STATUS_IOC_FAILURE);
		bfa_fsm_set_state(ioc, bfa_ioc_sm_fail);
		if (event != IOC_E_PFFAILED)
			bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_GETATTRFAIL);
		break;

	case IOC_E_DISABLE:
		bfa_ioc_timer_stop(ioc);
		bfa_fsm_set_state(ioc, bfa_ioc_sm_disabling);
		break;

	case IOC_E_ENABLE:
		break;

	default:
		bfa_sm_fault(ioc, event);
	}
}
