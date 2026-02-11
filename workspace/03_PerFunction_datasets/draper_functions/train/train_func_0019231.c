get_stdword (const char *s, void *v)
{
  struct e e, *r;

  e.s = s;
  e.n = -1;
  r = (struct e *) bsearch (&e, inv_std_dict,
			    sizeof(inv_std_dict)/sizeof(*inv_std_dict),
			    sizeof(*inv_std_dict), cmp);
  if (r)
    return r->n;
  else
    return -1;
}
