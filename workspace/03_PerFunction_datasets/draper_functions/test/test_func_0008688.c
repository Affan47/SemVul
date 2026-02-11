ds3232_work(struct work_struct *work)
{
	struct ds3232 *ds3232 = container_of(work, struct ds3232, work);
	struct i2c_client *client = ds3232->client;
	int stat, control;

	mutex_lock(&ds3232->mutex);

	stat = i2c_smbus_read_byte_data(client, DS3232_REG_SR);
	if (stat < 0)
		goto unlock;

	if (stat & DS3232_REG_SR_A1F) {
		control = i2c_smbus_read_byte_data(client, DS3232_REG_CR);
		if (control < 0) {
			pr_warn("Read Control Register error - Disable IRQ%d\n",
				client->irq);
		} else {

			control &= ~(DS3232_REG_CR_A1IE);
			i2c_smbus_write_byte_data(client, DS3232_REG_CR,
						control);


			stat &= ~DS3232_REG_SR_A1F;
			i2c_smbus_write_byte_data(client, DS3232_REG_SR, stat);

			rtc_update_irq(ds3232->rtc, 1, RTC_AF | RTC_IRQF);

			if (!ds3232->exiting)
				enable_irq(client->irq);
		}
	}

unlock:
	mutex_unlock(&ds3232->mutex);
}
