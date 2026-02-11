caml_string_equal(value s1, value s2)
{
  mlsize_t sz1, sz2;
  value * p1, * p2;

  if (s1 == s2) return Val_true;
  sz1 = Wosize_val(s1);
  sz2 = Wosize_val(s2);
  if (sz1 != sz2) return Val_false;
  for(p1 = Op_val(s1), p2 = Op_val(s2); sz1 > 0; sz1--, p1++, p2++)
    if (*p1 != *p2) return Val_false;
  return Val_true;
}
