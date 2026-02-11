eterms_count(Term t)
{
  return (t == NULL ? 0 : 1 + eterms_count(t->u.vp));
}
