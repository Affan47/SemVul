do_repeat_with_expander (int count,
			 const char * start,
			 const char * end,
			 const char * expander)
{
  sb one;
  sb many;

  sb_new (&one);
  if (!buffer_and_nest (start, end, &one, get_non_macro_line_sb))
    {
      as_bad (_("%s without %s"), start, end);
      return;
    }

  sb_new (&many);

  if (expander != NULL && strstr (one.ptr, expander) != NULL)
    {
      while (count -- > 0)
	{
	  int len;
	  char * sub;
	  sb processed;

	  sb_build (& processed, one.len);
	  sb_add_sb (& processed, & one);
	  sub = strstr (processed.ptr, expander);
	  len = sprintf (sub, "%d", count);
	  gas_assert (len < 8);
	  strcpy (sub + len, sub + 8);
	  processed.len -= (8 - len);
	  sb_add_sb (& many, & processed);
	  sb_kill (& processed);
	}
    }
  else
    while (count-- > 0)
      sb_add_sb (&many, &one);

  sb_kill (&one);

  input_scrub_include_sb (&many, input_line_pointer, 1);
  sb_kill (&many);
  buffer_limit = input_scrub_next_buffer (&input_line_pointer);
}
