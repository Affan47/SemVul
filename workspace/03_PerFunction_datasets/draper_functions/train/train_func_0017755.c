bna_ethport_sm_last_resp_wait(struct bna_ethport *ethport,
			enum bna_ethport_event event)
{
	switch (event) {
	case ETHPORT_E_FAIL:
		bfa_fsm_set_state(ethport, bna_ethport_sm_stopped);
		break;

	case ETHPORT_E_DOWN:


		break;

	case ETHPORT_E_FWRESP_UP_OK:

		bna_bfi_ethport_down(ethport);
		break;

	case ETHPORT_E_FWRESP_UP_FAIL:
	case ETHPORT_E_FWRESP_DOWN:
		bfa_fsm_set_state(ethport, bna_ethport_sm_stopped);
		break;

	default:
		bfa_sm_fault(event);
	}
}
