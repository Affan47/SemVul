cisco_card_find_nio_binding(struct cisco_card *card,u_int port_id)
{
   struct cisco_nio_binding *nb;

   if (!card)
      return NULL;

   for(nb=card->nio_list;nb;nb=nb->next)
      if (nb->port_id == port_id)
         return nb;

   return NULL;
}
