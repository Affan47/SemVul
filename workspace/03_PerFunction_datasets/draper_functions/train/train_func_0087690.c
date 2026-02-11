ov_time_tell(OggVorbis_File *vf){
  int link=0;
  ogg_int64_t pcm_total=0;
  double time_total=0.f;

  if(vf->ready_state<OPENED)return(OV_EINVAL);
  if(vf->seekable){
    pcm_total=ov_pcm_total(vf,-1);
    time_total=ov_time_total(vf,-1);


    for(link=vf->links-1;link>=0;link--){
      pcm_total-=vf->pcmlengths[link*2+1];
      time_total-=ov_time_total(vf,link);
      if(vf->pcm_offset>=pcm_total)break;
    }
  }

  return((double)time_total+(double)(vf->pcm_offset-pcm_total)/vf->vi[link].rate);
}
