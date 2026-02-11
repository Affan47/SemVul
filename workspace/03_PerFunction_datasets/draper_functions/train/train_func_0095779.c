allfiles_create_node (char *term, REFERENCE **fref)
{
  int i;
  struct text_buffer text;
  size_t off;
  FILE_BUFFER *fb;

  text_buffer_init (&text);
  text_buffer_printf (&text, _("File names matching `%s'"), term);
  text_buffer_add_char (&text, 0);
  off = text.off;

  text_buffer_printf (&text,
		      "\n\n%c\n%s %s\n\n"
		      "Info File Index\n"
		      "***************\n\n"
		      "File names that match `%s':\n\n"
		      "* Menu:\n\n",
		      INFO_COOKIE,
		      INFO_NODE_LABEL, text.base, term);

  memmove (text.base, text.base + off, text.off - off);
  text.off -= off;

  for (i = 0; fref[i]; i++)
    {
      text_buffer_printf (&text, "* %4i: (%s)", i+1, fref[i]->filename);
      if (fref[i]->nodename)
	text_buffer_printf (&text, "%s", fref[i]->nodename);
      text_buffer_printf (&text, ".\n");
    }

  fb = create_virtindex_file_buffer (NULL, text.base, text.off);
  allfiles_node = create_virtindex_node (fb);

  return allfiles_node;
}
