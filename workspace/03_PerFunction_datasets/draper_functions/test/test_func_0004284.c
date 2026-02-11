csio_init_intr_coalesce_parms(struct csio_hw *hw)
{
	struct csio_wrm *wrm = csio_hw_to_wrm(hw);
	struct csio_sge *sge = &wrm->sge;

	csio_sge_thresh_reg = csio_closest_thresh(sge, csio_intr_coalesce_cnt);
	if (csio_intr_coalesce_cnt) {
		csio_sge_thresh_reg = 0;
		csio_sge_timer_reg = X_TIMERREG_RESTART_COUNTER;
		return;
	}

	csio_sge_timer_reg = csio_closest_timer(sge, csio_intr_coalesce_time);
}
