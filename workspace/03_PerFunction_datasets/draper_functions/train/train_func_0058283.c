elan_isr(int irq, void *dev_id)
{
	struct elan_tp_data *data = dev_id;
	struct device *dev = &data->client->dev;
	int error;
	u8 report[ETP_MAX_REPORT_LEN];


	if (data->in_fw_update) {
		complete(&data->fw_completion);
		goto out;
	}

	error = data->ops->get_report(data->client, report);
	if (error)
		goto out;

	if (report[ETP_REPORT_ID_OFFSET] != ETP_REPORT_ID)
		dev_err(dev, "invalid report id data (%x)\n",
			report[ETP_REPORT_ID_OFFSET]);
	else
		elan_report_absolute(data, report);

out:
	return IRQ_HANDLED;
}
