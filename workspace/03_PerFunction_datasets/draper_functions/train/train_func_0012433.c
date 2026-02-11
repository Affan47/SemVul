InsertItem(int i, vtkObject *a)
{
  if( i >= this->NumberOfItems || !this->Top )
    {
    return;
    }

  vtkCollectionElement *elem;

  elem = new vtkCollectionElement;
  vtkCollectionElement *curr = this->Top;

  if( i < 0 )
    {
    this->Top = elem;
    elem->Next = curr;
    }
  else
    {
    vtkCollectionElement *next = curr->Next;

    int j = 0;
    while( j != i )
      {
      curr = next;
      next = curr->Next;
      j++;
      }

    curr->Next = elem;
    if( curr == this->Bottom )
      {
      this->Bottom = elem;
      }
    else
      {
      elem->Next = next;
      }
    }

  a->Register(this);
  elem->Item = a;

  this->Modified();

  this->NumberOfItems++;
}
