GetUserTransformMatrixMTime()
{
  unsigned long mTime = 0;
  unsigned long time;


  if ( this->UserMatrix != NULL )
    {
    mTime = this->UserMatrix->GetMTime();
    }

  if ( this->UserTransform != NULL )
    {
    time = this->UserTransform->GetMTime();
    mTime = ( time > mTime ? time : mTime );
    }


  return mTime;
}
