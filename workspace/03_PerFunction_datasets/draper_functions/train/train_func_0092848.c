cue_scanner_error(
      const char *error_string )
{
	if( cue_scanner_suppress_error == 0 )
	{
	        fprintf(
        	 stderr,
	         "%s at token: %s (offset: %" PRIzd " size: %" PRIzd ")\n",
        	 error_string,
	         cue_scanner_text,
	         cue_scanner_buffer_offset - (size_t) cue_scanner_leng,
	         (size_t) cue_scanner_leng );
	}
}
