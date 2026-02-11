igbvf_request_irq(struct igbvf_adapter *adapter)
{
	int err = -1;


	if (adapter->msix_entries)
		err = igbvf_request_msix(adapter);

	if (!err)
		return err;

	dev_err(&adapter->pdev->dev,
		"Unable to allocate interrupt, Error: %d\n", err);

	return err;
}
