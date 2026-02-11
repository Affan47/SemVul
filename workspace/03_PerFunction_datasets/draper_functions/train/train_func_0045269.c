print_predicate(FILE *fp, const struct predicate *p)
{
  fprintf (fp, "%s%s%s",
	   p->p_name,
	   p->arg_text ? " " : "",
	   p->arg_text ? p->arg_text : "");
}
