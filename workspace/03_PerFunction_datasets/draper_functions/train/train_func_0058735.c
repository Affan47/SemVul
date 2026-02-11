GetMTime()
{
  unsigned long mTime = this->vtkImageStencilSource::GetMTime();

  if ( this->Points != NULL )
    {
    unsigned long t = this->Points->GetMTime();
    if (t > mTime)
      {
      mTime = t;
      }
    }

  if ( !this->PointMap->empty() )
    {
    vtkLSSPointMap::iterator iter = this->PointMap->begin();
    while ( iter != this->PointMap->end() )
      {
      unsigned long t = iter->second->GetMTime();
      if (t > mTime)
        {
        mTime = t;
        }
      iter++;
      }
    }

  return mTime;
}
