do_spec (const char *spec)
{
  int value;

  value = do_spec_2 (spec);


  if (value == 0)
    {
      if (VEC_length (const_char_p, argbuf) > 0
	  && !strcmp (VEC_last (const_char_p, argbuf), "|"))
	VEC_pop (const_char_p, argbuf);

      set_collect_gcc_options ();

      if (VEC_length (const_char_p, argbuf) > 0)
	value = execute ();
    }

  return value;
}
