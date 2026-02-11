make_classification_flags(
						   struct pp_hwmgr *hwmgr,
						    USHORT classification,
						   USHORT classification2)
{
	PP_StateClassificationFlags result = 0;

	if (classification & ATOM_PPLIB_CLASSIFICATION_BOOT)
		result |= PP_StateClassificationFlag_Boot;

	if (classification & ATOM_PPLIB_CLASSIFICATION_THERMAL)
		result |= PP_StateClassificationFlag_Thermal;

	if (classification &
			ATOM_PPLIB_CLASSIFICATION_LIMITEDPOWERSOURCE)
		result |= PP_StateClassificationFlag_LimitedPowerSource;

	if (classification & ATOM_PPLIB_CLASSIFICATION_REST)
		result |= PP_StateClassificationFlag_Rest;

	if (classification & ATOM_PPLIB_CLASSIFICATION_FORCED)
		result |= PP_StateClassificationFlag_Forced;

	if (classification & ATOM_PPLIB_CLASSIFICATION_3DPERFORMANCE)
		result |= PP_StateClassificationFlag_3DPerformance;


	if (classification & ATOM_PPLIB_CLASSIFICATION_OVERDRIVETEMPLATE)
		result |= PP_StateClassificationFlag_ACOverdriveTemplate;

	if (classification & ATOM_PPLIB_CLASSIFICATION_UVDSTATE)
		result |= PP_StateClassificationFlag_Uvd;

	if (classification & ATOM_PPLIB_CLASSIFICATION_HDSTATE)
		result |= PP_StateClassificationFlag_UvdHD;

	if (classification & ATOM_PPLIB_CLASSIFICATION_SDSTATE)
		result |= PP_StateClassificationFlag_UvdSD;

	if (classification & ATOM_PPLIB_CLASSIFICATION_HD2STATE)
		result |= PP_StateClassificationFlag_HD2;

	if (classification & ATOM_PPLIB_CLASSIFICATION_ACPI)
		result |= PP_StateClassificationFlag_ACPI;

	if (classification2 & ATOM_PPLIB_CLASSIFICATION2_LIMITEDPOWERSOURCE_2)
		result |= PP_StateClassificationFlag_LimitedPowerSource_2;


	if (classification2 & ATOM_PPLIB_CLASSIFICATION2_ULV)
		result |= PP_StateClassificationFlag_ULV;

	if (classification2 & ATOM_PPLIB_CLASSIFICATION2_MVC)
		result |= PP_StateClassificationFlag_UvdMVC;

	return result;
}
