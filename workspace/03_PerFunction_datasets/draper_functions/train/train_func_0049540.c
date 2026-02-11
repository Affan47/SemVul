variable_symbols(Ilist syms)
{
  if (syms == NULL)
    return NULL;
  else {
    Ilist work = variable_symbols(syms->next);
    if (sn_to_arity(syms->i) == 0 && variable_name(sn_to_str(syms->i)))
      work = ilist_prepend(work, syms->i);
    return work;
  }
}
