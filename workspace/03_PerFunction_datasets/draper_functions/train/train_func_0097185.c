bfa_dconf_sm_flash_read(struct bfa_dconf_mod_s *dconf,
			enum bfa_dconf_event event)
{
	bfa_trc(dconf->bfa, event);

	switch (event) {
	case BFA_DCONF_SM_FLASH_COMP:
		bfa_timer_stop(&dconf->timer);
		bfa_sm_set_state(dconf, bfa_dconf_sm_ready);
		break;
	case BFA_DCONF_SM_TIMEOUT:
		bfa_sm_set_state(dconf, bfa_dconf_sm_ready);
		bfa_ioc_suspend(&dconf->bfa->ioc);
		break;
	case BFA_DCONF_SM_EXIT:
		bfa_timer_stop(&dconf->timer);
		bfa_sm_set_state(dconf, bfa_dconf_sm_uninit);
		bfa_fsm_send_event(&dconf->bfa->iocfc, IOCFC_E_DCONF_DONE);
		break;
	case BFA_DCONF_SM_IOCDISABLE:
		bfa_timer_stop(&dconf->timer);
		bfa_sm_set_state(dconf, bfa_dconf_sm_uninit);
		break;
	default:
		bfa_sm_fault(dconf->bfa, event);
	}
}
