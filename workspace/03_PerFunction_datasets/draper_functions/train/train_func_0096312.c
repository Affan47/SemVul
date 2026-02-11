bm_table(UC *p,I tlen)
{
  I *bm_array=ma(256);
  DO(256,bm_array[i]=tlen);
  DO(tlen,bm_array[p[i]]=tlen-(i+1));
  R bm_array;
}
