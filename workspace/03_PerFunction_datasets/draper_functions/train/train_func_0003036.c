ifconfig_pool_list (const struct ifconfig_pool* pool, struct status_output *out)
{
  if (pool && out)
    {
      struct gc_arena gc = gc_new ();
      int i;

      for (i = 0; i < pool->size; ++i)
	{
	  const struct ifconfig_pool_entry *e = &pool->list[i];
	  if (e->common_name)
	    {
	      const in_addr_t ip = ifconfig_pool_handle_to_ip_base (pool, i);
	      status_printf (out, "%s,%s",
			     e->common_name,
			     print_in_addr_t (ip, 0, &gc));
	    }
	}
      gc_free (&gc);
    }
}
