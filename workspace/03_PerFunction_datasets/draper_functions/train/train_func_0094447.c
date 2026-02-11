clear(void)
{
  unsigned int i;
  for (i=0; i<inputs_.size(); i++)
    inputs_[i] = 0.0;
  for (i=0; i<outputs_.size(); i++)
    outputs_[i] = 0.0;
}
