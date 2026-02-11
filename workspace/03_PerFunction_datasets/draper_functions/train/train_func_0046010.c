read_buffer(int bufnr, char *data, int cnt)
{
int n, buflen;
buffer_t *b = buffers+bufnr;

   pthread_mutex_lock( &b->mutex );
   buflen = (b->wpos-b->rpos)%b->len;
   if (buflen<0)
      buflen+=b->len;

   if (cnt>buflen)
      cnt=buflen;
   if (b->rpos+cnt > b->len)
      n=b->len-b->rpos;
   else
      n=cnt;
   bcopy (b->mem+b->rpos, data, n);
   b->rpos += n;
   cnt-=n;
   if (cnt>0)
   {
      bcopy (b->mem, data+n, cnt);
      b->rpos = cnt;
   }
   pthread_mutex_unlock ( &b->mutex);
   return n;
}
