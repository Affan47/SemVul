tick( StkFrames& frames, unsigned int channel )
{
  if ( channel >= frames.channels() ) {
    errorString_ << "Instrmnt::tick(): channel and StkFrames arguments are incompatible!";
    handleError( StkError::FUNCTION_ARGUMENT );
  }

  if ( frames.channels() == 1 ) {
    for ( unsigned int i=0; i<frames.frames(); i++ )
      frames[i] = tick();
  }
  else if ( frames.interleaved() ) {
    unsigned int hop = frames.channels();
    unsigned int index = channel;
    for ( unsigned int i=0; i<frames.frames(); i++ ) {
      frames[index] = tick();
      index += hop;
    }
  }
  else {
    unsigned int iStart = channel * frames.frames();
    for ( unsigned int i=0; i<frames.frames(); i++, iStart++ )
      frames[iStart] = tick();
  }

  return frames;
}
