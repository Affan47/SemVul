services_port_cmp(gconstpointer a, gconstpointer b, gpointer unused)
{
  port_type_t port_a, port_b;

  port_a = *(port_type_t *) a;
  port_b = *(port_type_t *) b;

  if (port_a > port_b)
    return 1;
  if (port_a < port_b)
    return -1;
  return 0;
}
