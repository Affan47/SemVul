format_with_decl (buffer, text, decl)
     output_buffer *buffer;
     text_info *text;
     tree decl;
{
  const char *p;


  for (p = text->format_spec; *p; ++p)
    {
      if (*p == '%')
	{
	  if (*(p + 1) == '%')
	    ++p;
	  else if (*(p + 1) != 's')
	    abort ();
	  else
	    break;
	}
    }


  maybe_wrap_text (buffer, text->format_spec, p);

  if (*p == '%')
    {
      const char *const n = (DECL_NAME (decl)
			     ? (*lang_hooks.decl_printable_name) (decl, 2)
			     : _("((anonymous))"));
      output_add_string (buffer, n);
      while (*p)
	{
	  ++p;
	  if (ISALPHA (*(p - 1) & 0xFF))
	    break;
	}
    }

  if (*p)
    {
      text->format_spec = p;
      output_format (buffer, text);
    }
}
