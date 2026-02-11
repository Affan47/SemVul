pp_macro_callback(const CMacroInfo *pmi)
{
  struct macro_cb_arg *a = pmi->arg;
  SV *s = a->string;
  dTHXa(a->interp);

  if (SvCUR(s) + pmi->definition_len + 10 >= SvLEN(s))
    SvGROW(s, 2*SvLEN(s));

  sv_catpvn(s, "#define ", 8);
  sv_catpvn(s, pmi->definition, pmi->definition_len);
  sv_catpvn(s, "\n", 1);
}
