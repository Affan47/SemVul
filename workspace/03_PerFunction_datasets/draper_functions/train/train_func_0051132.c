vorbis_analysis(vorbis_block *vb, ogg_packet *op){
  int ret,i;
  vorbis_block_internal *vbi=vb->internal;

  vb->glue_bits=0;
  vb->time_bits=0;
  vb->floor_bits=0;
  vb->res_bits=0;


  for(i=0;i<PACKETBLOBS;i++)
    oggpack_reset(vbi->packetblob[i]);


  if((ret=_mapping_P[0]->forward(vb)))
    return(ret);

  if(op){
    if(vorbis_bitrate_managed(vb))


      return(OV_EINVAL);

    op->packet=oggpack_get_buffer(&vb->opb);
    op->bytes=oggpack_bytes(&vb->opb);
    op->b_o_s=0;
    op->e_o_s=vb->eofflag;
    op->granulepos=vb->granulepos;
    op->packetno=vb->sequence;
  }
  return(0);
}
