reset(void)
{
  time_ = (StkFloat) 0.0;
  for ( unsigned int i=0; i<lastOutputs_.size(); i++ )
    lastOutputs_[i] = 0.0;
  finished_ = false;
}
