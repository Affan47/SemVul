computeSample( void )
{


  while ( time_ < 0.0 )
    time_ += TABLE_SIZE;
  while ( time_ >= TABLE_SIZE )
    time_ -= TABLE_SIZE;

  StkFloat tyme;
  if ( phaseOffset_ ) {
    tyme = time_ + phaseOffset_;
    while ( tyme < 0.0 )
      tyme += TABLE_SIZE;
    while ( tyme >= TABLE_SIZE )
      tyme -= TABLE_SIZE;
  }
  else {
    tyme = time_;
  }

  lastOutput_ = table_.interpolate( tyme );


  time_ += rate_;

  return lastOutput_;
}
