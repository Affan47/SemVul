vorbis_block_clear(vorbis_block *vb){
  int i;
  vorbis_block_internal *vbi=vb->internal;

  _vorbis_block_ripcord(vb);
  if(vb->localstore)_ogg_free(vb->localstore);

  if(vbi){
    for(i=0;i<PACKETBLOBS;i++){
      oggpack_writeclear(vbi->packetblob[i]);
      if(i!=PACKETBLOBS/2)_ogg_free(vbi->packetblob[i]);
    }
    _ogg_free(vbi);
  }
  memset(vb,0,sizeof(*vb));
  return(0);
}
