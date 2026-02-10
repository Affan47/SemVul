output_epd_writer(FILE* epd_file, at_string name,
		      int llx, int lly, int urx, int ury,
		      at_output_opts_type * opts,
		      spline_list_array_type shape,
		      at_msg_func msg_func,
		      at_address msg_data)
{
    int result;

    result = output_epd_header(epd_file, name, llx, lly, urx, ury);
    if (result != 0)
	return result;

    out_splines(epd_file, shape);

    return 0;
}
