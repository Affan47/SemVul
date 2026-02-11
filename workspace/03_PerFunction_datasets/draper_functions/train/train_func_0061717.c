odf_master_styles_to_xl_styles (GnmOOExport *state)
{
	int i;

	for (i = 0; i < workbook_sheet_count (state->wb); i++) {
		Sheet const *sheet = workbook_sheet_by_index (state->wb, i);

		if (sheet->print_info->page_setup == NULL)
			print_info_load_defaults (sheet->print_info);

		if (sheet->print_info->header != NULL) {
			odf_hf_region_to_xl_styles
				(state, sheet->print_info->header->left_format);
			odf_hf_region_to_xl_styles
				(state, sheet->print_info->header->middle_format);
			odf_hf_region_to_xl_styles
				(state, sheet->print_info->header->right_format);
		}
		if (sheet->print_info->footer != NULL) {
			odf_hf_region_to_xl_styles
				(state, sheet->print_info->footer->left_format);
			odf_hf_region_to_xl_styles
				(state, sheet->print_info->footer->middle_format);
			odf_hf_region_to_xl_styles
				(state, sheet->print_info->footer->right_format);
		}
	}
}
