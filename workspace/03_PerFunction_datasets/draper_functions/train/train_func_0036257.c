resize( size_t nFrames, unsigned int nChannels, StkFloat value )
{
  this->resize( nFrames, nChannels );

  for ( size_t i=0; i<size_; i++ ) data_[i] = value;
}
