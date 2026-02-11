ogg_sync_buffer(ogg_sync_state *oy, s32 size){


  if(oy->returned){
    oy->fill-=oy->returned;
    if(oy->fill>0)
      memmove(oy->data,oy->data+oy->returned,oy->fill);
    oy->returned=0;
  }

  if(size>oy->storage-oy->fill){

    s32 newsize=size+oy->fill+4096;

    if(oy->data)
      oy->data = (unsigned char *)gf_realloc(oy->data,newsize);
    else
      oy->data = (unsigned char *)gf_malloc(newsize);
    oy->storage=newsize;
  }


  return((char *)oy->data+oy->fill);
}
