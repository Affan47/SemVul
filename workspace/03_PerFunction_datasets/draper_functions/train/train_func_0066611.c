ov_bitrate(OggVorbis_File *vf,int i){
  if(vf->ready_state<OPENED)return(OV_EINVAL);
  if(i>=vf->links)return(OV_EINVAL);
  if(!vf->seekable && i!=0)return(ov_bitrate(vf,0));
  if(i<0){
    ogg_int64_t bits=0;
    int i;
    float br;
    for(i=0;i<vf->links;i++)
      bits+=(vf->offsets[i+1]-vf->dataoffsets[i])*8;


    br = bits/ov_time_total(vf,-1);
    return(rint(br));
  }else{
    if(vf->seekable){

      return(rint((vf->offsets[i+1]-vf->dataoffsets[i])*8/ov_time_total(vf,i)));
    }else{

      if(vf->vi[i].bitrate_nominal>0){
	return vf->vi[i].bitrate_nominal;
      }else{
	if(vf->vi[i].bitrate_upper>0){
	  if(vf->vi[i].bitrate_lower>0){
	    return (vf->vi[i].bitrate_upper+vf->vi[i].bitrate_lower)/2;
	  }else{
	    return vf->vi[i].bitrate_upper;
	  }
	}
	return(OV_FALSE);
      }
    }
  }
}
