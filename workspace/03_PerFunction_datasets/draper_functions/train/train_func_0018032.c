init(SAMPLE_BUFFER* insample)
{
  i.init(insample);

  set_channels(insample->number_of_channels());

  buffer.resize(insample->number_of_channels());
  for(size_t i = 0; i < buffer.size(); i++)
    buffer[i].clear();

}
