isci_task_request_build(struct isci_host *ihost,
						    struct isci_remote_device *idev,
						    u16 tag, struct isci_tmf *isci_tmf)
{
	enum sci_status status = SCI_FAILURE;
	struct isci_request *ireq = NULL;
	struct domain_device *dev;

	dev_dbg(&ihost->pdev->dev,
		"%s: isci_tmf = %p\n", __func__, isci_tmf);

	dev = idev->domain_dev;


	ireq = isci_tmf_request_from_tag(ihost, isci_tmf, tag);
	if (!ireq)
		return NULL;


	status = sci_task_request_construct(ihost, idev, tag,
					     ireq);

	if (status != SCI_SUCCESS) {
		dev_warn(&ihost->pdev->dev,
			 "%s: sci_task_request_construct failed - "
			 "status = 0x%x\n",
			 __func__,
			 status);
		return NULL;
	}


	if (dev->dev_type == SAS_END_DEVICE) {
		isci_tmf->proto = SAS_PROTOCOL_SSP;
		status = sci_task_request_construct_ssp(ireq);
		if (status != SCI_SUCCESS)
			return NULL;
	}

	return ireq;
}
