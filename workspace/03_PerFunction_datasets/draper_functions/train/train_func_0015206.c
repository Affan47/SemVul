bfa_iocpf_sm_reset(struct bfa_iocpf *iocpf, enum iocpf_event event)
{
	switch (event) {
	case IOCPF_E_ENABLE:
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_fwcheck);
		break;

	case IOCPF_E_STOP:
		break;

	default:
		bfa_sm_fault(event);
	}
}
