isci_request_ssp_request_construct(
	struct isci_request *request)
{
	enum sci_status status;

	dev_dbg(&request->isci_host->pdev->dev,
		"%s: request = %p\n",
		__func__,
		request);
	status = sci_io_request_construct_basic_ssp(request);
	return status;
}
