ti_bandgap_talert_irq_handler(int irq, void *data)
{
	struct ti_bandgap *bgp = data;
	struct temp_sensor_registers *tsr;
	u32 t_hot = 0, t_cold = 0, ctrl;
	int i;

	spin_lock(&bgp->lock);
	for (i = 0; i < bgp->conf->sensor_count; i++) {
		tsr = bgp->conf->sensors[i].registers;
		ctrl = ti_bandgap_readl(bgp, tsr->bgap_status);


		t_hot = ctrl & tsr->status_hot_mask;


		t_cold = ctrl & tsr->status_cold_mask;

		if (!t_cold && !t_hot)
			continue;

		ctrl = ti_bandgap_readl(bgp, tsr->bgap_mask_ctrl);


		if (t_hot) {
			ctrl &= ~tsr->mask_hot_mask;
			ctrl |= tsr->mask_cold_mask;
		} else if (t_cold) {
			ctrl &= ~tsr->mask_cold_mask;
			ctrl |= tsr->mask_hot_mask;
		}

		ti_bandgap_writel(bgp, ctrl, tsr->bgap_mask_ctrl);

		dev_dbg(bgp->dev,
			"%s: IRQ from %s sensor: hotevent %d coldevent %d\n",
			__func__, bgp->conf->sensors[i].domain,
			t_hot, t_cold);


		if (bgp->conf->report_temperature)
			bgp->conf->report_temperature(bgp, i);
	}
	spin_unlock(&bgp->lock);

	return IRQ_HANDLED;
}
