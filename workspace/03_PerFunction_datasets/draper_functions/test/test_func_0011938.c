get_prop_string (se_t *se, se_o_t *o, se_prop_t *p)
{
  if (p->reader)
  {
    se_prop_read_t v;
    p->reader (p, &v);
    return v.s;
  }

  return p->value;
}
