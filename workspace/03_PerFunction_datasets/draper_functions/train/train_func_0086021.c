setFrequency(StkFloat frequency)
{
  StkFloat freakency = frequency;
  if ( frequency <= 0.0 ) {
    errorString_ << "Clarinet::setFrequency: parameter is less than or equal to zero!";
    handleError( StkError::WARNING );
    freakency = 220.0;
  }


  StkFloat delay = (Stk::sampleRate() / freakency) * 0.5 - 1.5;
  if (delay <= 0.0) delay = 0.3;
  else if (delay > length_) delay = length_;
  delayLine_.setDelay(delay);
}
