ogg_stream_init(ogg_stream_state *os,s32 serialno){
  if(os){
    memset(os,0,sizeof(*os));
    os->body_storage=16*1024;
    os->body_data = (unsigned char *)gf_malloc(os->body_storage*sizeof(*os->body_data));

    os->lacing_storage=1024;
    os->lacing_vals=(s32 *)gf_malloc(os->lacing_storage*sizeof(*os->lacing_vals));
    os->granule_vals=(s64*)gf_malloc(os->lacing_storage*sizeof(*os->granule_vals));

    os->serialno=serialno;

    return(0);
  }
  return(-1);
}
