latex2e_write_blank_multicolumn_cell (GsfOutput *output, int start_col,
				      G_GNUC_UNUSED int start_row,
				      int num_merged_cols, int num_merged_rows,
				      gint index,
				      GnmStyleBorderType *borders, Sheet *sheet)
{
	int merge_width = 0;
	GnmStyleBorderType left_border = GNM_STYLE_BORDER_NONE;
	GnmStyleBorderType right_border = GNM_STYLE_BORDER_NONE;

	if (num_merged_cols > 1 || num_merged_rows > 1) {
		ColRowInfo const * ci;
		int i;

		for (i = 0; i < num_merged_cols; i++) {
			ci = sheet_col_get_info (sheet, start_col + i);
			merge_width += ci->size_pixels;
		}
	}

	if (index == 0) {
		left_border = *borders;
	}
	right_border = borders[index + num_merged_cols];


	if (num_merged_cols > 1) {
		int i;


		gsf_output_printf (output, "\\multicolumn{%d}{", num_merged_cols);

		if (left_border != GNM_STYLE_BORDER_NONE)
			latex2e_print_vert_border (output, left_border);

		if (num_merged_rows > 1) {
			gsf_output_printf (output, "c");
		} else {
			gsf_output_printf (output, "p{");
			for (i = 0; i < num_merged_cols; i++) {
				gsf_output_printf (output, "\t\\gnumericCol%s+%%\n",
					 col_name (start_col + i));
			}
			gsf_output_printf (output, "\t\\tabcolsep*2*%i}", num_merged_cols - 1);
		}

		if (right_border != GNM_STYLE_BORDER_NONE)
			latex2e_print_vert_border (output, right_border);


		gsf_output_printf (output,"}%%\n\t{");
	} else if (left_border != GNM_STYLE_BORDER_NONE || right_border != GNM_STYLE_BORDER_NONE) {


		gsf_output_printf (output, "\\multicolumn{1}{");

		if (left_border != GNM_STYLE_BORDER_NONE)
			latex2e_print_vert_border (output, left_border);


		gsf_output_printf (output, "p{\\gnumericCol%s}", col_name(start_col));

		if (right_border != GNM_STYLE_BORDER_NONE)
			latex2e_print_vert_border (output, right_border);


		gsf_output_printf (output,"}%%\n\t{");

	}

	if (num_merged_rows > 1) {
		int i;

		gsf_output_printf (output, "\\setlength{\\gnumericMultiRowLength}{0pt}%%\n");
		for (i = 0; i < num_merged_cols; i++) {
			gsf_output_printf (output, "\t \\addtolength{\\gnumericMultiRowLength}{\\gnumericCol%s}%%\n", col_name (start_col + i));
			if (i>0)
				gsf_output_printf (output, "\t \\addtolength{\\gnumericMultiRowLength}{\\tabcolsep}%%\n");
		}
		gsf_output_printf (output, "\t \\multirow{%i}[%i]{\\gnumericMultiRowLength}{%%\n\t ", num_merged_rows, num_merged_rows/2);


		gsf_output_printf (output, "}");
	}


	if (num_merged_cols > 1 || left_border != GNM_STYLE_BORDER_NONE
	    || right_border != GNM_STYLE_BORDER_NONE)
		gsf_output_printf (output, "}");


	gsf_output_printf (output, "\n");

}
