appendmatrix_latex (GelOutput *gelo, GelMatrixW *m, gboolean nice)
{
	int i, j;
	if (nice && gelo->cur_line_pos != 0)
		gel_output_string (gelo, "\n");
	gel_output_string (gelo, "\\left[ \\begin{array}{");
	for (i = 0; i < gel_matrixw_width (m); i++)
		gel_output_string (gelo, "r");
	gel_output_string (gelo, "}");
	if (nice)
		gel_output_string (gelo, "\n");
	else
		gel_output_string (gelo, " ");

	for (j = 0; j < gel_matrixw_height (m); j++) {
		gel_print_etree (gelo,
				 gel_matrixw_index (m, 0, j),
				 FALSE);
		for(i = 1; i < gel_matrixw_width (m); i++) {
			gel_output_string (gelo, " & ");
			gel_print_etree (gelo,
					 gel_matrixw_index (m, i, j),
					 FALSE);
		}
		gel_output_string (gelo, " \\\\");
		if (nice)
			gel_output_string (gelo, "\n");
		else
			gel_output_string (gelo, " ");
	}

	gel_output_string (gelo, "\\end{array} \\right]");
}
