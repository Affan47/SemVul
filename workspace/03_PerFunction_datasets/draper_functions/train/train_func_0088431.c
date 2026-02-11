ov_pcm_seek(OggVorbis_File *vf,ogg_int64_t pos){
  int thisblock,lastblock=0;
  int ret=ov_pcm_seek_page(vf,pos);
  codec_setup_info *ci=vf->vi->codec_setup;
  if(ret<0)return(ret);


  while(1){
    ogg_packet op;
    ogg_page og;

    int ret=ogg_stream_packetpeek(&vf->os,&op);
    if(ret>0){
      thisblock=vorbis_packet_blocksize(vf->vi+vf->current_link,&op);
      if(lastblock)vf->pcm_offset+=(lastblock+thisblock)>>2;

      if(vf->pcm_offset+((thisblock+ci->blocksizes[1])>>2)>=pos)break;

      ogg_stream_packetout(&vf->os,NULL);


      if(op.granulepos>-1){
        int i;

        vf->pcm_offset=op.granulepos;
        for(i=0;i<vf->current_link;i++)
          vf->pcm_offset+=vf->pcmlengths[i];
      }

      lastblock=thisblock;

    }else{
      if(ret<0 && ret!=-3)break;


      if(_get_next_page(vf,&og,-1)<0)break;
      if(vf->current_serialno!=ogg_page_serialno(&og))_decode_clear(vf);

      if(vf->ready_state<STREAMSET){
        int link;

        vf->current_serialno=ogg_page_serialno(&og);
        for(link=0;link<vf->links;link++)
          if(vf->serialnos[link]==vf->current_serialno)break;
        if(link==vf->links)return(-137);
        vf->current_link=link;

        ogg_stream_init(&vf->os,vf->current_serialno);
        ogg_stream_reset(&vf->os);
        vf->ready_state=STREAMSET;
        lastblock=0;
      }
      ogg_stream_pagein(&vf->os,&og);
    }
  }


  _make_decode_ready(vf);
  while(vf->pcm_offset<pos){
    float **pcm;
    long target=pos-vf->pcm_offset;
    long samples=vorbis_synthesis_pcmout(&vf->vd,&pcm);

    if(samples>target)samples=target;
    vorbis_synthesis_read(&vf->vd,samples);
    vf->pcm_offset+=samples;

    if(samples<target)
      if(_process_packet(vf,1)<=0)
        vf->pcm_offset=ov_pcm_total(vf,-1);
  }
  return 0;
}
