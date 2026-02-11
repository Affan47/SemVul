do_recovery(struct pci_dev *dev, int severity)
{
	pci_ers_result_t status, result = PCI_ERS_RESULT_RECOVERED;
	enum pci_channel_state state;

	if (severity == AER_FATAL)
		state = pci_channel_io_frozen;
	else
		state = pci_channel_io_normal;

	status = broadcast_error_message(dev,
			state,
			"error_detected",
			report_error_detected);

	if (severity == AER_FATAL) {
		result = reset_link(dev);
		if (result != PCI_ERS_RESULT_RECOVERED)
			goto failed;
	}

	if (status == PCI_ERS_RESULT_CAN_RECOVER)
		status = broadcast_error_message(dev,
				state,
				"mmio_enabled",
				report_mmio_enabled);

	if (status == PCI_ERS_RESULT_NEED_RESET) {


		status = broadcast_error_message(dev,
				state,
				"slot_reset",
				report_slot_reset);
	}

	if (status != PCI_ERS_RESULT_RECOVERED)
		goto failed;

	broadcast_error_message(dev,
				state,
				"resume",
				report_resume);

	dev_info(&dev->dev, "AER: Device recovery successful\n");
	return;

failed:

	dev_info(&dev->dev, "AER: Device recovery failed\n");
}
