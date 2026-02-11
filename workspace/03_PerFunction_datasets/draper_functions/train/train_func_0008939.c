bcm5600_send_pkt_to_cpu(struct nm_16esw_data *d,
                                   struct bcm5600_pkt *p)
{
   m_uint32_t pkt_addr,pkt_len,dot1q_data;


   if (p->sent_to_cpu)
      return(FALSE);

   pkt_addr = p->rdes[0];
   pkt_len  = p->pkt_len;

   if (p->orig_vlan != -1) {

      physmem_copy_to_vm(d->vm,p->pkt,pkt_addr,pkt_len);
   } else {

      physmem_copy_to_vm(d->vm,p->pkt,pkt_addr,N_ETH_HLEN - 2);


      dot1q_data = (N_ETH_PROTO_DOT1Q << 16) | p->real_vlan;
      physmem_copy_u32_to_vm(d->vm,pkt_addr+N_ETH_HLEN-2,dot1q_data);


      physmem_copy_to_vm(d->vm,p->pkt+N_ETH_HLEN-2,
                         pkt_addr+sizeof(n_eth_dot1q_hdr_t),
                         pkt_len - (N_ETH_HLEN - 2));
      pkt_len += 4;
   }

   physmem_copy_u32_to_vm(d->vm,d->rx_current+0x14,0x40000000 + (pkt_len+4));
   physmem_copy_u32_to_vm(d->vm,d->rx_current+0x18,0x100 + p->ingress_port);
   p->sent_to_cpu = TRUE;

#if DEBUG_RECEIVE
   BCM_LOG(d,"sending packet to CPU (orig_vlan=%d).\n",p->orig_vlan);
#endif
   return(TRUE);
}
