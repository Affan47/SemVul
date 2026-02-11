unqueue_end()
{
   unsigned int *ptr=txbuf_sta;

   while (ptr!=txbuf_end)
   {
      if(*ptr==TX_END)
      {
         fprintf(stderr,"removing TX_END!\n");
         *ptr=TX_DUMMY;
      }
      ptr++;
      if (ptr>=txbuf+TXBUFSIZE)
         ptr=txbuf;
   }
}
