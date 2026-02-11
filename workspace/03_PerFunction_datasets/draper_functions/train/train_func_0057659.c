bna_rxf_sm_stopped(struct bna_rxf *rxf, enum bna_rxf_event event)
{
	switch (event) {
	case RXF_E_START:
		bfa_fsm_set_state(rxf, bna_rxf_sm_cfg_wait);
		break;

	case RXF_E_STOP:
		call_rxf_stop_cbfn(rxf);
		break;

	case RXF_E_FAIL:

		break;

	case RXF_E_CONFIG:
		call_rxf_cam_fltr_cbfn(rxf);
		break;

	default:
		bfa_sm_fault(event);
	}
}
