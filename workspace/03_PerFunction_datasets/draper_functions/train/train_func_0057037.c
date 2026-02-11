vorbis_packet_blocksize(vorbis_info *vi,ogg_packet *op){
  codec_setup_info     *ci=vi->codec_setup;
  oggpack_buffer       opb;
  int                  mode;

  oggpack_readinit(&opb,op->packet,op->bytes);


  if(oggpack_read(&opb,1)!=0){

    return(OV_ENOTAUDIO);
  }

  {
    int modebits=0;
    int v=ci->modes;
    while(v>1){
      modebits++;
      v>>=1;
    }


    mode=oggpack_read(&opb,modebits);
  }
  if(mode==-1)return(OV_EBADPACKET);
  return(ci->blocksizes[ci->mode_param[mode]->blockflag]);
}
