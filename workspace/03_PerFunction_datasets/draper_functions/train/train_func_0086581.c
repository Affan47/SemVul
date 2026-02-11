acpi_dma_update_dma_spec(struct acpi_dma *adma,
		struct acpi_dma_spec *dma_spec)
{

	dma_spec->dev = adma->dev;


	if (adma->base_request_line == 0 && adma->end_request_line == 0)
		return 0;


	if (dma_spec->slave_id < adma->base_request_line ||
	    dma_spec->slave_id > adma->end_request_line)
		return -1;


	dma_spec->slave_id -= adma->base_request_line;

	return 1;
}
