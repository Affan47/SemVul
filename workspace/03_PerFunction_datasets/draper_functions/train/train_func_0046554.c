output_pdf_writer(FILE* pdf_file, at_string name,
		      int llx, int lly, int urx, int ury,
		      at_output_opts_type * opts,
		      spline_list_array_type shape,
		      at_msg_func msg_func,
		      at_address msg_data)
{
    int result;
    size_t length = 0;

#ifdef _WINDOWS
    if(pdf_file == stdout)
	  {
        fprintf(stderr, "This driver couldn't write to stdout!\n");
        return -1;
      }
#endif

    result = output_pdf_header(pdf_file, name, llx, lly, urx, ury);
    if (result != 0)
	return result;

    out_splines(pdf_file, shape, &length);

	output_pdf_tailor(pdf_file, length, llx, lly, urx, ury);

    return 0;
}
