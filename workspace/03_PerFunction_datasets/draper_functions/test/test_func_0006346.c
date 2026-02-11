GetMTime()
{
  unsigned long mTime=this-> vtkObject::GetMTime();
  unsigned long time;

  if ( this->RenderWindow != NULL )
    {
    time = this->RenderWindow->GetMTime();
    mTime = ( time > mTime ? time : mTime );
    }
  return mTime;
}
