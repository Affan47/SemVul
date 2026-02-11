protocol_stack_sub_pkt(protostack_t *pstk, const packet_info_t * packet)
{
  guint i = 0;
  GList *item = NULL;
  protocol_t *protocol = NULL;

  g_assert(pstk);

  if (!packet)
    return;


  while ((i <= STACK_SIZE) && packet->prot_desc->protonames[i])
    {
      item = g_list_find_custom (pstk->protostack[i],
                                 packet->prot_desc->protonames[i],
                                 protocol_compare);
      if (!item)
        {
          g_my_critical
            ("Protocol not found while subtracting packet in protocol_stack_sub_pkt");
          break;
        }
      protocol = item->data;

      g_assert( !strcmp(protocol->name, packet->prot_desc->protonames[i]));
      basic_stats_sub(&protocol->stats, packet->size);
      i++;
    }
}
