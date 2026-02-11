odf_write_covered_cell (GnmOOExport *state, int *num)
{
	if (*num > 0) {
		gsf_xml_out_start_element (state->xml, TABLE "covered-table-cell");
		if (*num > 1)
			gsf_xml_out_add_int (state->xml,
					     TABLE "number-columns-repeated",
					     *num);
		gsf_xml_out_end_element (state->xml);
		*num = 0;
	}
}
