read_begin (void)
{
  const char *p;

  pobegin ();
  obj_read_begin_hook ();


  obstack_begin (&notes, chunksize);
  obstack_begin (&cond_obstack, chunksize);


  for (p = line_separator_chars; *p; p++)
    is_end_of_line[(unsigned char) *p] = 2;


  if (flag_mri)
    lex_type['?'] = 3;
}
