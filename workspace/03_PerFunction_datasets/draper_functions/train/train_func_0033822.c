spmi_regulator_vs_ocp_isr(int irq, void *data)
{
	struct spmi_regulator *vreg = data;
	ktime_t ocp_irq_time;
	s64 ocp_trigger_delay_us;

	ocp_irq_time = ktime_get();
	ocp_trigger_delay_us = ktime_us_delta(ocp_irq_time,
						vreg->vs_enable_time);


	if (ocp_trigger_delay_us > SPMI_VS_OCP_FAULT_DELAY_US)
		vreg->ocp_count = 0;


	udelay(SPMI_VS_OCP_FALL_DELAY_US);

	vreg->ocp_count++;

	if (vreg->ocp_count == 1) {

		spmi_regulator_vs_clear_ocp(vreg);
	} else if (vreg->ocp_count <= vreg->ocp_max_retries) {

		schedule_delayed_work(&vreg->ocp_work,
			msecs_to_jiffies(vreg->ocp_retry_delay_ms) + 1);
	} else {
		dev_err(vreg->dev,
			"OCP triggered %d times; no further retries\n",
			vreg->ocp_count);
	}

	return IRQ_HANDLED;
}
