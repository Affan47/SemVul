ti_bandgap_update_alert_threshold(struct ti_bandgap *bgp, int id,
					     int val, bool hot)
{
	struct temp_sensor_data *ts_data = bgp->conf->sensors[id].ts_data;
	struct temp_sensor_registers *tsr;
	u32 thresh_val, reg_val, t_hot, t_cold, ctrl;
	int err = 0;

	tsr = bgp->conf->sensors[id].registers;


	thresh_val = ti_bandgap_readl(bgp, tsr->bgap_threshold);
	t_cold = (thresh_val & tsr->threshold_tcold_mask) >>
		__ffs(tsr->threshold_tcold_mask);
	t_hot = (thresh_val & tsr->threshold_thot_mask) >>
		__ffs(tsr->threshold_thot_mask);
	if (hot)
		t_hot = val;
	else
		t_cold = val;

	if (t_cold > t_hot) {
		if (hot)
			err = ti_bandgap_add_hyst(bgp, t_hot,
						  -ts_data->hyst_val,
						  &t_cold);
		else
			err = ti_bandgap_add_hyst(bgp, t_cold,
						  ts_data->hyst_val,
						  &t_hot);
	}


	reg_val = thresh_val &
		  ~(tsr->threshold_thot_mask | tsr->threshold_tcold_mask);
	reg_val |= (t_hot << __ffs(tsr->threshold_thot_mask)) |
		   (t_cold << __ffs(tsr->threshold_tcold_mask));


	if (TI_BANDGAP_HAS(bgp, ERRATA_813)) {

		ctrl = ti_bandgap_readl(bgp, tsr->bgap_mask_ctrl);

		if (hot)
			ctrl &= ~tsr->mask_hot_mask;
		else
			ctrl &= ~tsr->mask_cold_mask;

		ti_bandgap_writel(bgp, ctrl, tsr->bgap_mask_ctrl);
	}


	ti_bandgap_writel(bgp, reg_val, tsr->bgap_threshold);

	if (TI_BANDGAP_HAS(bgp, ERRATA_813)) {

		ctrl = ti_bandgap_readl(bgp, tsr->bgap_mask_ctrl);
		if (hot)
			ctrl |= tsr->mask_hot_mask;
		else
			ctrl |= tsr->mask_cold_mask;

		ti_bandgap_writel(bgp, ctrl, tsr->bgap_mask_ctrl);
	}

	if (err) {
		dev_err(bgp->dev, "failed to reprogram thot threshold\n");
		err = -EIO;
		goto exit;
	}

	ti_bandgap_unmask_interrupts(bgp, id, t_hot, t_cold);
exit:
	return err;
}
