eq_specializations (const void *p1, const void *p2)
{
  const spec_entry *e1 = (const spec_entry *)p1;
  const spec_entry *e2 = (const spec_entry *)p2;
  int equal;

  ++comparing_specializations;
  equal = (e1->tmpl == e2->tmpl
	   && comp_template_args (e1->args, e2->args));
  --comparing_specializations;

  return equal;
}
