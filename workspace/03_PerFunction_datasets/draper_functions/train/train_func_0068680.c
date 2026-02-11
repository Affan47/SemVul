gt_eth_handle_rx_daddr(struct gt_data *d,
                                         struct eth_port *port,
                                         u_int hash_res,
                                         m_uint64_t hash_entry)
{

   if (hash_res == GT_HTLOOKUP_HOP_EXCEEDED)
      return(1);


   if ((hash_res == GT_HTLOOKUP_MATCH) && (hash_entry & GT_HTE_RD))
      return(2);


   if ((hash_res == GT_HTLOOKUP_MISS) && (port->pcr & GT_PCR_HDM))
      return(2);


   if (port->pcr & GT_PCR_PM)
      return(1);


   return(0);
}
