acpi_resource_to_address64(struct acpi_resource *resource,
			   struct acpi_resource_address64 *out)
{
	struct acpi_resource_address16 *address16;
	struct acpi_resource_address32 *address32;

	if (!resource || !out) {
		return (AE_BAD_PARAMETER);
	}


	switch (resource->type) {
	case ACPI_RESOURCE_TYPE_ADDRESS16:

		address16 =
		    ACPI_CAST_PTR(struct acpi_resource_address16,
				  &resource->data);
		ACPI_COPY_ADDRESS(out, address16);
		break;

	case ACPI_RESOURCE_TYPE_ADDRESS32:

		address32 =
		    ACPI_CAST_PTR(struct acpi_resource_address32,
				  &resource->data);
		ACPI_COPY_ADDRESS(out, address32);
		break;

	case ACPI_RESOURCE_TYPE_ADDRESS64:


		memcpy(out, &resource->data,
		       sizeof(struct acpi_resource_address64));
		break;

	default:

		return (AE_BAD_PARAMETER);
	}

	return (AE_OK);
}
