GetMTime()
{
  unsigned long mTime=this->Superclass::GetMTime();
  unsigned long time;

  if (this->Interpolate != 0 && this->Interpolator != NULL)
    {
    time = this->Interpolator->GetMTime();
    mTime = ( time > mTime ? time : mTime );
    }

  return mTime;
}
