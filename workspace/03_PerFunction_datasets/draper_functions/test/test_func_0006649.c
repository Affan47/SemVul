InsertHandleOnLine(double* pos)
{
  if ( this->NumberOfHandles < 3 &&
       this->LinePoints->GetNumberOfPoints() > 2 )
    {
    return;
    }

  int id = this->LinePicker->GetCellId();
  if ( id == -1 ){ return; }

  this->TemporaryHandlePoints->Reset();
  this->TemporaryHandlePoints->SetNumberOfTuples(this->NumberOfHandles+1);
  int i;
  for ( i = 0; i <= id; i++ )
    {
    this->TemporaryHandlePoints->SetTuple(i,this->HandleGeometry[i]->GetCenter());
    }

  this->TemporaryHandlePoints->SetTuple(id+1,pos);

  for ( i = id + 1; i < this->NumberOfHandles; ++i )
    {
    this->TemporaryHandlePoints->SetTuple(i+1,this->HandleGeometry[i]->GetCenter());
    }

  this->AllocateHandles(this->TemporaryHandlePoints->GetNumberOfTuples());

  for ( i = 0; i < this->NumberOfHandles; ++i )
    {
    this->AdjustHandlePosition(i,this->TemporaryHandlePoints->GetTuple(i));
    }
}
