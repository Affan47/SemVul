encoding_resolve_composite_font (struct a2ps_job * job,
				  struct encoding * encoding,
				  const char * font_list)
{
  const char * res = NULL;
  char * font_list_copy;
  char * font_name;

  astrcpy (font_list_copy, font_list);
  font_name = strtok (font_list_copy, ",<>;");


  res = pair_get (encoding->composite, font_name);


  if (!res)
    {
      res = pair_get (encoding->composite, "default_composite__");

      if (!res)
	error (1, 0, "Cannot find font %s, nor any composite font",
	       font_name);
    }

  message (msg_enc,
	   (stderr, "In encoding %s, font %s is resolved as %s\n",
	    encoding->key, font_name, res));
  return res;
}
