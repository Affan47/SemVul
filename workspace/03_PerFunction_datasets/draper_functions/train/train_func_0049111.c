lpfc_poll_timeout(unsigned long ptr)
{
	struct lpfc_hba *phba = (struct lpfc_hba *) ptr;

	if (phba->cfg_poll & ENABLE_FCP_RING_POLLING) {
		lpfc_sli_handle_fast_ring_event(phba,
			&phba->sli.ring[LPFC_FCP_RING], HA_R0RE_REQ);

		if (phba->cfg_poll & DISABLE_FCP_RING_INT)
			lpfc_poll_rearm_timer(phba);
	}
}
