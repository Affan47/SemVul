vorbis_encode_setup_vbr(vorbis_info *vi,
			    long  channels,
			    long  rate,
			    float quality){
  codec_setup_info *ci=vi->codec_setup;
  highlevel_encode_setup *hi=&ci->hi;

  quality+=.0000001;
  if(quality>=1.)quality=.9999;

  get_setup_template(vi,channels,rate,quality,0);
  if(!hi->setup)return OV_EIMPL;

  return vorbis_encode_setup_setting(vi,channels,rate);
}
