RemoveObserver(unsigned long tag)
{
  vtkObserver *elem;
  vtkObserver *prev;
  vtkObserver *next;

  elem = this->Start;
  prev = NULL;
  while (elem)
    {
    if (elem->Tag == tag)
      {
      if (prev)
        {
        prev->Next = elem->Next;
        next = prev->Next;
        }
      else
        {
        this->Start = elem->Next;
        next = this->Start;
        }
      delete elem;
      elem = next;
      }
    else
      {
      prev = elem;
      elem = elem->Next;
      }
    }

  this->ListModified = 1;
}
