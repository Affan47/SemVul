complementary_share(Formula a, Formula b)
{
  return
    (a->type == NOT_FORM && formula_ident_share(a->kids[0], b))
    ||
    (b->type == NOT_FORM && formula_ident_share(a, b->kids[0]));
}
