get_did(struct intel_opregion *opregion, int i)
{
	u32 did;

	if (i < ARRAY_SIZE(opregion->acpi->didl)) {
		did = opregion->acpi->didl[i];
	} else {
		i -= ARRAY_SIZE(opregion->acpi->didl);

		if (WARN_ON(i >= ARRAY_SIZE(opregion->acpi->did2)))
			return 0;

		did = opregion->acpi->did2[i];
	}

	return did;
}
