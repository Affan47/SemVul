ogg_stream_iovecin(ogg_stream_state *os, ogg_iovec_t *iov, int count,
                       long e_o_s, ogg_int64_t granulepos){

  int bytes = 0, lacing_vals, i;

  if(ogg_stream_check(os)) return -1;
  if(!iov) return 0;

  for (i = 0; i < count; ++i) bytes += (int)iov[i].iov_len;
  lacing_vals=bytes/255+1;

  if(os->body_returned){


    os->body_fill-=os->body_returned;
    if(os->body_fill)
      memmove(os->body_data,os->body_data+os->body_returned,
              os->body_fill);
    os->body_returned=0;
  }


  if(_os_body_expand(os,bytes) || _os_lacing_expand(os,lacing_vals))
    return -1;


  for (i = 0; i < count; ++i) {
    memcpy(os->body_data+os->body_fill, iov[i].iov_base, iov[i].iov_len);
    os->body_fill += (int)iov[i].iov_len;
  }


  for(i=0;i<lacing_vals-1;i++){
    os->lacing_vals[os->lacing_fill+i]=255;
    os->granule_vals[os->lacing_fill+i]=os->granulepos;
  }
  os->lacing_vals[os->lacing_fill+i]=bytes%255;
  os->granulepos=os->granule_vals[os->lacing_fill+i]=granulepos;


  os->lacing_vals[os->lacing_fill]|= 0x100;

  os->lacing_fill+=lacing_vals;


  os->packetno++;

  if(e_o_s)os->e_o_s=1;

  return(0);
}
