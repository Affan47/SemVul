_os_body_expand(ogg_stream_state *os,s32 needed){
  if(os->body_storage<=os->body_fill+needed){
    os->body_storage+=(needed+1024);
    os->body_data = (unsigned char *)gf_realloc(os->body_data,os->body_storage*sizeof(*os->body_data));
  }
}
