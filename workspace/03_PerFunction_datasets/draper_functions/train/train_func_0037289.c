set_sample_coding(ECA_AUDIO_FORMAT::Sample_coding v)
{
  sc_rep = v;


  set_sample_format_string(format_string());
}
