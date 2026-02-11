route_string (const struct route *r, struct gc_arena *gc)
{
  struct buffer out = alloc_buf_gc (256, gc);
  buf_printf (&out, "ROUTE network %s netmask %s gateway %s",
	      print_in_addr_t (r->network, 0, gc),
	      print_in_addr_t (r->netmask, 0, gc),
	      print_in_addr_t (r->gateway, 0, gc)
	      );
  if (r->metric_defined)
    buf_printf (&out, " metric %d", r->metric);
  return BSTR (&out);
}
