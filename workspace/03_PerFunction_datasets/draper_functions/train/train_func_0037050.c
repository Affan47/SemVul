radeon_atcs_verify_interface(acpi_handle handle,
					struct radeon_atcs *atcs)
{
	union acpi_object *info;
	struct atcs_verify_interface output;
	size_t size;
	int err = 0;

	info = radeon_atcs_call(handle, ATCS_FUNCTION_VERIFY_INTERFACE, NULL);
	if (!info)
		return -EIO;

	memset(&output, 0, sizeof(output));

	size = *(u16 *) info->buffer.pointer;
	if (size < 8) {
		DRM_INFO("ATCS buffer is too small: %zu\n", size);
		err = -EINVAL;
		goto out;
	}
	size = min(sizeof(output), size);

	memcpy(&output, info->buffer.pointer, size);


	DRM_DEBUG_DRIVER("ATCS version %u\n", output.version);

	radeon_atcs_parse_functions(&atcs->functions, output.function_bits);

out:
	kfree(info);
	return err;
}
