rule_new_internal_regexp (struct pattern *pattern,
			  char *regexp, int regexp_len,
			  struct darray *rhs,
			  const char *filename, size_t line)
{
  struct rule *res = XMALLOC (struct rule, 1);
  const char *error_msg;


  res->word = (uchar *) pattern->pattern;


  res->regex = XMALLOC (struct re_pattern_buffer, 1);
  res->regex->translate = NULL;
  res->regex->fastmap = NULL;
  res->regex->buffer = NULL;
  res->regex->allocated = 0;

  error_msg = re_compile_pattern (regexp, regexp_len, res->regex);

  if (error_msg)
    error_at_line (1, 0, filename, line,
		   _("cannot compile regular expression `%s': %s"),
		   regexp, error_msg);
  free (pattern);
  res->rhs = rhs;
  return res;
}
