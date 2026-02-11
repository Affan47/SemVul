bcm5600_insert_arl_entry(struct nm_16esw_data *d)
{
   struct bcm5600_table *table = d->t_arl;
   m_uint32_t *entry,mask;
   int i,index;

   mask = BCM5600_ARL_VLAN_TAG_MASK | BCM5600_ARL_MAC_MSB_MASK;

   for(i=0;i<d->arl_cnt[0]-1;i++) {
      entry = bcm5600_table_get_entry(d,table,i);


      if ((entry[0] == d->dw[1]) && ((entry[1] & mask) == (d->dw[2] & mask))) {
         entry[0] = d->dw[1];
         entry[1] = d->dw[2];
         entry[2] = d->dw[3];
         d->dw[1] = i;
         return(0);
      }
   }

   index = d->arl_cnt[0] - 1;

   entry = bcm5600_table_get_entry(d,table,index);
   entry[0] = d->dw[1];
   entry[1] = d->dw[2];
   entry[2] = d->dw[3];
   d->dw[1] = index;

   d->arl_cnt[0]++;
   return(0);
}
