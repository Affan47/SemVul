add_unit_addr (struct backtrace_state *state, uintptr_t base_address,
	       struct unit_addrs addrs,
	       backtrace_error_callback error_callback, void *data,
	       struct unit_addrs_vector *vec)
{
  struct unit_addrs *p;


  addrs.low += base_address;
  addrs.high += base_address;


  if (vec->count > 0)
    {
      p = (struct unit_addrs *) vec->vec.base + (vec->count - 1);
      if ((addrs.low == p->high || addrs.low == p->high + 1)
	  && addrs.u == p->u)
	{
	  if (addrs.high > p->high)
	    p->high = addrs.high;
	  return 1;
	}
    }

  p = ((struct unit_addrs *)
       backtrace_vector_grow (state, sizeof (struct unit_addrs),
			      error_callback, data, &vec->vec));
  if (p == NULL)
    return 0;

  *p = addrs;
  ++vec->count;
  return 1;
}
