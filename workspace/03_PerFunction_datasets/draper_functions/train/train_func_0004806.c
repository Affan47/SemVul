elim_rebind(Formula f, Ilist uvars)
{
  if (quant_form(f)) {
    Term var = get_rigid_term(f->qvar, 0);
    Ilist uvars_plus;

    if (ilist_member(uvars, SYMNUM(var))) {


      int sn = gen_new_symbol("y", 0, uvars);
      Term newvar = get_rigid_term(sn_to_str(sn), 0);
      subst_free_var(f->kids[0], var, newvar);
      f->qvar = sn_to_str(sn);
      free_term(var);
      var = newvar;
    }

    uvars_plus = ilist_prepend(uvars, SYMNUM(var));
    f->kids[0] = elim_rebind(f->kids[0], uvars_plus);
    free_term(var);
    free_ilist(uvars_plus);
    return f;
  }
  else {
    int i;
    for (i = 0; i < f->arity; i++)
      f->kids[i] = elim_rebind(f->kids[i], uvars);
    return f;
  }
}
