uf_skip_zero(MI_COLUMNDEF *rec, MI_BIT_BUFF *bit_buff, uchar *to,
			  uchar *end)
{
  if (get_bit(bit_buff))
    bzero((char*) to,(uint) (end-to));
  else
    decode_bytes(rec,bit_buff,to,end);
}
