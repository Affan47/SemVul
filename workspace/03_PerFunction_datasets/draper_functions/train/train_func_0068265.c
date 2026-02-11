EnableAllSelectionArrays(vtkDataArraySelection *s)
{
  unsigned long int mTime = s->GetMTime();
  s->EnableAllArrays();
  if (mTime != s->GetMTime())
    {
    this->Modified();
    }
}
