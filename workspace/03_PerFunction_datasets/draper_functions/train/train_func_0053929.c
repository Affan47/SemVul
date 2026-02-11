BL_block_filename()
{
  char *buf_token;

  BL_field_seen = TRUE;
  if (MA_field_seen) {
    sprintf(ErrorBuffer,
	    "MA field already used.  Cannot have both the BL and the MA");
    ErrorReport(WARNING_ERR_LVL);
    sprintf(ErrorBuffer,
	    "fields.  Ignoring the BL line.\n");
    ErrorReport(WARNING_ERR_LVL);
  }

  buf_token = get_token(NULL);
  insert_file(buf_token, BLOCK_FILES);
}
