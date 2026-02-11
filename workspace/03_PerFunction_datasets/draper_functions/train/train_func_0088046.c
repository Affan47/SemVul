_make_decode_ready(OggVorbis_File *vf){
  if(vf->ready_state!=STREAMSET)return;
  if(vf->seekable){
    vorbis_synthesis_init(&vf->vd,vf->vi+vf->current_link);
  }else{
    vorbis_synthesis_init(&vf->vd,vf->vi);
  }
  vorbis_block_init(&vf->vd,&vf->vb);
  vf->ready_state=INITSET;
  return;
}
