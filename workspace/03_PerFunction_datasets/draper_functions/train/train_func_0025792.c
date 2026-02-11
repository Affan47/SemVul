lastOut( void ) const
{
  if ( lastOutputs_.empty() ) return 0.0;

  if ( lastOutputs_.size() == 1 )
    return lastOutputs_[0];

  StkFloat output = 0.0;
  for ( unsigned int i=0; i<lastOutputs_.size(); i++ ) {
    output += lastOutputs_[i];
  }
  return output / lastOutputs_.size();
}
