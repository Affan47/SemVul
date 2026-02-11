jpeg_set_marker_processor (j_decompress_ptr cinfo, int marker_code,
			   jpeg_marker_parser_method routine)
{
  my_marker_ptr marker = (my_marker_ptr) cinfo->marker;

  if (marker_code == (int) M_COM)
    marker->process_COM = routine;
  else if (marker_code >= (int) M_APP0 && marker_code <= (int) M_APP15)
    marker->process_APPn[marker_code - (int) M_APP0] = routine;
  else
    ERREXIT1(cinfo, JERR_UNKNOWN_MARKER, marker_code);
}
