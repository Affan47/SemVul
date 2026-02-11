do_pragma (buf, limit, op, keyword)
     U_CHAR *buf, *limit;
     FILE_BUF *op;
     struct directive *keyword;
{
  SKIP_WHITE_SPACE (buf);
  if (!strncmp ((char *) buf, "once", 4)) {


    if (!instack[indepth].system_header_p)
      warning ("`#pragma once' is obsolete");
    do_once ();
  }

  if (!strncmp ((char *) buf, "implementation", 14)) {


    int h;
    U_CHAR *p = buf + 14, *fname;
    SKIP_WHITE_SPACE (p);
    if (*p == '\n' || *p != '\"')
      return 0;

    fname = p + 1;
    if ((p = (U_CHAR *) strchr ((char *) fname, '\"')))
      *p = '\0';

    for (h = 0; h < INCLUDE_HASHSIZE; h++) {
      struct include_file *inc;
      for (inc = include_hashtab[h]; inc; inc = inc->next) {
	if (!strcmp (base_name (inc->fname), (char *) fname)) {
	  warning ("`#pragma implementation' for \"%s\" appears after its #include",fname);
	  return 0;
	}
      }
    }
  }
  return 0;
}
