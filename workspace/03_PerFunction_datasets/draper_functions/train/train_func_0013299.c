setDelay(StkFloat delay)
{
  StkFloat outPointer;

  if ( delay > inputs_.size() - 1 ) {
    errorString_ << "DelayL::setDelay: argument (" << delay << ") too big ... setting to maximum!";
    handleError( StkError::WARNING );


    outPointer = inPoint_ + 1.0;
    delay_ = inputs_.size() - 1;
  }
  else if (delay < 0 ) {
    errorString_ << "DelayL::setDelay: argument (" << delay << ") less than zero ... setting to zero!";
    handleError( StkError::WARNING );

    outPointer = inPoint_;
    delay_ = 0;
  }
  else {
    outPointer = inPoint_ - delay;
    delay_ = delay;
  }

  while (outPointer < 0)
    outPointer += inputs_.size();

  outPoint_ = (long) outPointer;
  if ( outPoint_ == inputs_.size() ) outPoint_ = 0;
  alpha_ = outPointer - outPoint_;
  omAlpha_ = (StkFloat) 1.0 - alpha_;
}
