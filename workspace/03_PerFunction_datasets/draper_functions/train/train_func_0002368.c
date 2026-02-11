flat_multiset_vars(Flatterm f)
{
  I2list vars = NULL;
  Flatterm fi;
  for (fi = f; fi != f->end->next; fi = fi->next)
    if (VARIABLE(fi))
      vars = multiset_add(vars, VARNUM(fi));
  return vars;
}
