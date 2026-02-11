GetMTime()
{
  unsigned long mTime=this->vtkProp::GetMTime();
  unsigned long time;
  vtkProp *part;

  vtkCollectionSimpleIterator pit;
  for (this->Parts->InitTraversal(pit);
       (part=this->Parts->GetNextProp(pit)); )
    {
    time = part->GetMTime();
    mTime = ( time > mTime ? time : mTime );
    }

  return mTime;
}
