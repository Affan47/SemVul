expand_to_temp_buffer (buf, limit, output_marks, assertions)
     U_CHAR *buf, *limit;
     int output_marks, assertions;
{
  register FILE_BUF *ip;
  FILE_BUF obuf;
  int length = limit - buf;
  U_CHAR *buf1;
  int odepth = indepth;
  int save_assertions_flag = assertions_flag;

  assertions_flag = assertions;

  if (length < 0)
    abort ();


  buf1 = (U_CHAR *) alloca (length + 1);
  {
    register U_CHAR *p1 = buf;
    register U_CHAR *p2 = buf1;

    while (p1 != limit)
      *p2++ = *p1++;
  }
  buf1[length] = 0;


  obuf.length = length * 2 + 100;
  obuf.bufp = obuf.buf = (U_CHAR *) xmalloc (obuf.length);
  obuf.fname = 0;
  obuf.macro = 0;
  obuf.free_ptr = 0;

  CHECK_DEPTH ({return obuf;});

  ++indepth;

  ip = &instack[indepth];
  ip->fname = 0;
  ip->nominal_fname = 0;
  ip->inc = 0;
  ip->system_header_p = 0;
  ip->macro = 0;
  ip->free_ptr = 0;
  ip->length = length;
  ip->buf = ip->bufp = buf1;
  ip->if_stack = if_stack;

  ip->lineno = obuf.lineno = 1;


  rescan (&obuf, output_marks);


  --indepth;

  if (indepth != odepth)
    abort ();


  obuf.length = obuf.bufp - obuf.buf;

  assertions_flag = save_assertions_flag;
  return obuf;
}
