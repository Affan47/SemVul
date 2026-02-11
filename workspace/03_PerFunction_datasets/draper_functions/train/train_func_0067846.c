atm_store_fifo(struct atm_seg_context *asc)
{
   size_t len;

   len = m_min(asc->buf_len,asc->txfifo_avail);

   memcpy(&asc->txfifo_cell[asc->txfifo_pos],asc->buffer,len);
   asc->buffer += len;
   asc->buf_len -= len;
   asc->txfifo_pos += len;
   asc->txfifo_avail -= len;

   if (!asc->txfifo_avail) {
      atm_send_fifo(asc);
      return(TRUE);
   }

   return(FALSE);
}
