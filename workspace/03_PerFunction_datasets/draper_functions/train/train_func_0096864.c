dev_mueslix_set_nio(struct mueslix_data *d,u_int channel_id,
                        netio_desc_t *nio)
{
   struct mueslix_channel *channel;

   if (channel_id >= MUESLIX_NR_CHANNELS)
      return(-1);

   channel = &d->channel[channel_id];


   if (channel->nio != NULL)
      return(-1);


   channel->nio = nio;
   channel->tx_tid = ptask_add((ptask_callback)dev_mueslix_handle_txring,
                               channel,NULL);
   netio_rxl_add(nio,(netio_rx_handler_t)dev_mueslix_handle_rxring,
                 channel,NULL);
   return(0);
}
