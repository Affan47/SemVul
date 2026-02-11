literal_to_term(Literals l)
{
  Term t;
  if (l->sign)
    t = copy_term(l->atom);
  else {
    t = get_rigid_term(not_sym(), 1);
    ARG(t,0) = copy_term(l->atom);
  }
  return t;
}
