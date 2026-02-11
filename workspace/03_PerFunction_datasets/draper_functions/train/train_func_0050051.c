strip_quantifiers(Formula f)
{
  while (quant_form(f))
    f = f->kids[0];
  return f;
}
