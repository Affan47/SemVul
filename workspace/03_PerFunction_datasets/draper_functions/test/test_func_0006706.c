acpi_get_dma_attr(struct acpi_device *adev)
{
	if (!acpi_dma_supported(adev))
		return DEV_DMA_NOT_SUPPORTED;

	if (adev->flags.coherent_dma)
		return DEV_DMA_COHERENT;
	else
		return DEV_DMA_NON_COHERENT;
}
