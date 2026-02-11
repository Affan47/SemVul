_dmalloc_strcat(const char *file, const int line,
			 char *to, const char *from)
{
  if (BIT_IS_SET(_dmalloc_flags, DEBUG_CHECK_FUNCS)) {
    if ((! dmalloc_verify_pnt(file, line, "strcat", to,
			      0 ,
			      loc_strlen(file, line, "strcat", to)
			      + loc_strlen(file, line, "strcat", from) + 1))
	|| (! dmalloc_verify_pnt(file, line, "strcat", from,
				 0 , -1))) {
      dmalloc_message("bad pointer argument found in strcat");
    }
  }
  return (char *)strcat(to, from);
}
