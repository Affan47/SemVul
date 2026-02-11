e752x_check_ns_interface(struct e752x_error_info *info,
				int *error_found, int handle_error)
{
	u32 stat32;

	stat32 = info->nsi_ferr;
	if (stat32 & NSI_ERR_MASK) {
		if (stat32 & NSI_FATAL_MASK)
			nsi_error(1, stat32 & NSI_FATAL_MASK, error_found,
				  handle_error);
		if (stat32 & NSI_NON_FATAL_MASK)
			nsi_error(0, stat32 & NSI_NON_FATAL_MASK, error_found,
				  handle_error);
	}
	stat32 = info->nsi_nerr;
	if (stat32 & NSI_ERR_MASK) {
		if (stat32 & NSI_FATAL_MASK)
			nsi_error(1, stat32 & NSI_FATAL_MASK, error_found,
				  handle_error);
		if (stat32 & NSI_NON_FATAL_MASK)
			nsi_error(0, stat32 & NSI_NON_FATAL_MASK, error_found,
				  handle_error);
	}
}
