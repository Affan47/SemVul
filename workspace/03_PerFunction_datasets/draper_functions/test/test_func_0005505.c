ti1570_add_tx_padding(struct pa_a1_data *d,m_uint32_t len)
{
   if (len > d->txfifo_avail) {
      TI1570_LOG(d,"ti1570_add_tx_padding: trying to add too large "
                 "padding (avail: 0x%x, pad: 0x%x)\n",d->txfifo_avail,len);
      len = d->txfifo_avail;
   }

   memset(&d->txfifo_cell[d->txfifo_pos],0,len);
   d->txfifo_pos += len;
   d->txfifo_avail -= len;
}
