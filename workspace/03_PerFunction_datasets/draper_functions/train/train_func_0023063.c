vorbis_block_init(vorbis_dsp_state *v, vorbis_block *vb){
  int i;
  memset(vb,0,sizeof(*vb));
  vb->vd=v;
  vb->localalloc=0;
  vb->localstore=NULL;
  if(v->analysisp){
    vorbis_block_internal *vbi=
      vb->internal=_ogg_calloc(1,sizeof(vorbis_block_internal));
    vbi->ampmax=-9999;

    for(i=0;i<PACKETBLOBS;i++){
      if(i==PACKETBLOBS/2){
	vbi->packetblob[i]=&vb->opb;
      }else{
	vbi->packetblob[i]=
	  _ogg_calloc(1,sizeof(oggpack_buffer));
      }
      oggpack_writeinit(vbi->packetblob[i]);
    }
  }

  return(0);
}
