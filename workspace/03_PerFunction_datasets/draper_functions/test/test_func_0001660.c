validate_else (p, limit)
     register U_CHAR *p;
     register U_CHAR *limit;
{

  while (1) {
    while (*p == '\\' && p[1] == '\n')
      p += 2;
    if (is_hor_space[*p])
      p++;
    else if (*p == '/') {
      while (p[1] == '\\' && p[2] == '\n')
	p += 2;
      if (p[1] == '*') {


	for (p += 2; ; p++) {
	  if (p == limit)
	    return;
	  if (*p == '*') {
	    while (p[1] == '\\' && p[2] == '\n')
	      p += 2;
	    if (p[1] == '/') {
	      p += 2;
	      break;
	    }
	  }
	}
      }
      else if (cplusplus_comments && p[1] == '/')
	return;
      else break;
    } else break;
  }
  if (*p != '\n')
    pedwarn ("text following `#else' or `#endif' violates ANSI standard");
}
