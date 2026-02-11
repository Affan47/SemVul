make_classification_flags(struct pp_hwmgr *hwmgr,
		uint16_t classification, uint16_t classification2)
{
	uint32_t result = 0;

	if (classification & ATOM_PPLIB_CLASSIFICATION_BOOT)
		result |= PP_StateClassificationFlag_Boot;

	if (classification & ATOM_PPLIB_CLASSIFICATION_THERMAL)
		result |= PP_StateClassificationFlag_Thermal;

	if (classification & ATOM_PPLIB_CLASSIFICATION_LIMITEDPOWERSOURCE)
		result |= PP_StateClassificationFlag_LimitedPowerSource;

	if (classification & ATOM_PPLIB_CLASSIFICATION_REST)
		result |= PP_StateClassificationFlag_Rest;

	if (classification & ATOM_PPLIB_CLASSIFICATION_FORCED)
		result |= PP_StateClassificationFlag_Forced;

	if (classification & ATOM_PPLIB_CLASSIFICATION_ACPI)
		result |= PP_StateClassificationFlag_ACPI;

	if (classification2 & ATOM_PPLIB_CLASSIFICATION2_LIMITEDPOWERSOURCE_2)
		result |= PP_StateClassificationFlag_LimitedPowerSource_2;

	return result;
}
