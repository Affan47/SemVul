GetMTime()
{
  unsigned long mTime = this->Superclass::GetMTime();
  unsigned long t;


  vtkCollectionSimpleIterator pit;
  this->Images->InitTraversal(pit);
  vtkImageSlice *image = 0;
  while ( (image = this->Images->GetNextImage(pit)) != 0)
    {
    t = image->GetMTime();
    mTime = (t < mTime ? mTime : t);
    }

  return mTime;
}
