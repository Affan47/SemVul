GetMTime()
{
  unsigned long mTime=this->Superclass::GetMTime();
  unsigned long posMTime, fpMTime, vupMTime, vaMTime, psMTime, crMTime;

  if ( this->PositionInterpolator )
    {
    posMTime = this->PositionInterpolator->GetMTime();
    mTime = (posMTime > mTime ? posMTime : mTime);
    }
  if ( this->FocalPointInterpolator )
    {
    fpMTime = this->FocalPointInterpolator->GetMTime();
    mTime = (fpMTime > mTime ? fpMTime : mTime);
    }
  if ( this->ViewUpInterpolator )
    {
    vupMTime = this->ViewUpInterpolator->GetMTime();
    mTime = (vupMTime > mTime ? vupMTime : mTime);
    }
  if ( this->ViewAngleInterpolator )
    {
    vaMTime = this->ViewAngleInterpolator->GetMTime();
    mTime = (vaMTime > mTime ? vaMTime : mTime);
    }
  if ( this->ParallelScaleInterpolator )
    {
    psMTime = this->ParallelScaleInterpolator->GetMTime();
    mTime = (psMTime > mTime ? psMTime : mTime);
    }
  if ( this->ClippingRangeInterpolator )
    {
    crMTime = this->ClippingRangeInterpolator->GetMTime();
    mTime = (crMTime > mTime ? crMTime : mTime);
    }

  return mTime;
}
