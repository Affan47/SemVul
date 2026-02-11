ov_raw_total(OggVorbis_File *vf,int i){
  if(vf->ready_state<OPENED)return(-131);
  if(!vf->seekable || i>=vf->links)return(-131);
  if(i<0){
    long acc=0;
    int i;
    for(i=0;i<vf->links;i++)
      acc+=ov_raw_total(vf,i);
    return(acc);
  }else{
    return(vf->offsets[i+1]-vf->offsets[i]);
  }
}
