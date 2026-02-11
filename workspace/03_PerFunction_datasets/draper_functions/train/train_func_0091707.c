csio_hws_quiescing(struct csio_hw *hw, enum csio_hw_ev evt)
{
	hw->prev_evt = hw->cur_evt;
	hw->cur_evt = evt;
	CSIO_INC_STATS(hw, n_evt_sm[evt]);

	switch (evt) {
	case CSIO_HWE_QUIESCED:
		switch (hw->evtflag) {
		case CSIO_HWE_FW_DLOAD:
			csio_set_state(&hw->sm, csio_hws_resetting);


		case CSIO_HWE_HBA_RESET:
			csio_set_state(&hw->sm, csio_hws_resetting);

			csio_notify_lnodes(hw, CSIO_LN_NOTIFY_HWRESET);
			csio_wr_destroy_queues(hw, false);
			csio_do_reset(hw, false);
			csio_post_event(&hw->sm, CSIO_HWE_HBA_RESET_DONE);
			break;

		case CSIO_HWE_PCI_REMOVE:
			csio_set_state(&hw->sm, csio_hws_removing);
			csio_notify_lnodes(hw, CSIO_LN_NOTIFY_HWREMOVE);
			csio_wr_destroy_queues(hw, true);

			csio_do_bye(hw);
			break;

		case CSIO_HWE_SUSPEND:
			csio_set_state(&hw->sm, csio_hws_quiesced);
			break;

		case CSIO_HWE_PCIERR_DETECTED:
			csio_set_state(&hw->sm, csio_hws_pcierr);
			csio_wr_destroy_queues(hw, false);
			break;

		default:
			CSIO_INC_STATS(hw, n_evt_unexp);
			break;

		}
		break;

	default:
		CSIO_INC_STATS(hw, n_evt_unexp);
		break;
	}
}
