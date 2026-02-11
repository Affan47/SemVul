da9052_ts_input_close(struct input_dev *input_dev)
{
	struct da9052_tsi *tsi = input_get_drvdata(input_dev);

	tsi->stopped = true;
	mb();
	da9052_disable_irq(tsi->da9052, DA9052_IRQ_PENDOWN);
	cancel_delayed_work_sync(&tsi->ts_pen_work);

	if (tsi->adc_on) {
		da9052_disable_irq(tsi->da9052, DA9052_IRQ_TSIREADY);
		da9052_ts_adc_toggle(tsi, false);


		da9052_enable_irq(tsi->da9052, DA9052_IRQ_PENDOWN);
	}


	da9052_reg_update(tsi->da9052, DA9052_TSI_CONT_A_REG, 1 << 1, 0);
}
