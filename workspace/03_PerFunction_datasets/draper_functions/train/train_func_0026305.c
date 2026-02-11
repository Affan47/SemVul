bfa_ioc_sm_fail_retry(struct bfa_ioc *ioc, enum ioc_event event)
{
	switch (event) {
	case IOC_E_ENABLED:
		bfa_fsm_set_state(ioc, bfa_ioc_sm_getattr);
		break;

	case IOC_E_PFFAILED:
	case IOC_E_HWERROR:


		ioc->cbfn->enable_cbfn(ioc->bfa, BFA_STATUS_IOC_FAILURE);
		bfa_fsm_set_state(ioc, bfa_ioc_sm_fail);
		if (event != IOC_E_PFFAILED)
			bfa_iocpf_initfail(ioc);
		break;

	case IOC_E_HWFAILED:
		ioc->cbfn->enable_cbfn(ioc->bfa, BFA_STATUS_IOC_FAILURE);
		bfa_fsm_set_state(ioc, bfa_ioc_sm_hwfail);
		break;

	case IOC_E_ENABLE:
		break;

	case IOC_E_DISABLE:
		bfa_fsm_set_state(ioc, bfa_ioc_sm_disabling);
		break;

	case IOC_E_DETACH:
		bfa_fsm_set_state(ioc, bfa_ioc_sm_uninit);
		bfa_iocpf_stop(ioc);
		break;

	default:
		bfa_sm_fault(event);
	}
}
