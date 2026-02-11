visit_regex(struct process_data *procdata, void *context)
{
  struct regular_expression *p = context;
  const size_t len = strlen(procdata->munged_filename);

  int rv = re_search (&p->regex, procdata->munged_filename,
		      len, 0, len,
		      (struct re_registers *) NULL);
  if (rv < 0)
    {
      return VISIT_REJECTED;
    }
  else
    {
      return VISIT_ACCEPTED;
    }
}
