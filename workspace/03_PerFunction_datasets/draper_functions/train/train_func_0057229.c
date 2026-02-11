get_tcp_name (name_add_t *nt)
{
  guint8 th_off_x2;
  guint8 tcp_len;


  if (appdata.mode == TCP)
    {
      gchar *numeric_name, *resolved_name;
      int type = nt->node_id.addr.tcp4.host.type;
      int shift = type == AF_INET6 ? 2 : 0;

      if (nt->dir == OUTBOUND)
          fill_node_id(&nt->node_id, TCP, nt, -8<<shift, 0, type);
      else
          fill_node_id(&nt->node_id, TCP, nt, -4<<shift, 2, type);

      numeric_name = g_strdup_printf("%s:%d",
                      address_to_str(&nt->node_id.addr.tcp4.host),
                      nt->node_id.addr.tcp4.port);

      if (pref.name_res)
        {
          const gchar *dnsname;
          const port_service_t *port;
          dnsname = dns_lookup (&nt->node_id.addr.tcp4.host);
          port = services_tcp_find(nt->node_id.addr.tcp4.port);
          if (port)
            resolved_name = g_strdup_printf("%s:%s", dnsname, port->name);
          else
            resolved_name = g_strdup_printf("%s:%d", dnsname,
                                            nt->node_id.addr.tcp4.port);
        }
      else
        resolved_name = NULL;

      add_name (numeric_name, resolved_name, &nt->node_id, nt);

      g_free (numeric_name);
      g_free (resolved_name);
    }

  if (nt->packet_size <= nt->offset + 14)
    {
      missing_data_msg(nt, "TCP");
      return FALSE;
    }

  th_off_x2 = *(guint8 *) (nt->p + nt->offset + 12);
  tcp_len = hi_nibble (th_off_x2) * 4;
  nt->offset += tcp_len;
  return TRUE;
}
