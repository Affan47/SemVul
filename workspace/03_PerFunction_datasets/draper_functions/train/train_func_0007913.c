uri_make_path(Uri *uri, char *str)
{
  int i;
  char *decoded_part;
  Ds ds;


  if (str == NULL || *str == '\0')
	return(0);


  if ((uri->path_parts = strsplitd(str, "/", 0, 1)) == NULL)
	return(-1);

  ds_init(&ds);
  for (i = 0; i < dsvec_len(uri->path_parts); i++) {
	char *part;

	part = (char *) dsvec_ptr_index(uri->path_parts, i);
	if (!uri_is_valid_path_part(part))
	  return(-1);

	if ((decoded_part = url_decode(part, NULL, NULL)) == NULL)
	  return(-1);

	ds_asprintf(&ds, "%s", decoded_part);
  }
  uri->path = ds_buf(&ds);

  return(dsvec_len(uri->path_parts));
}
