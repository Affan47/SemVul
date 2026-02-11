IsAPoint(OTTetra *t, vtkIdType id)
{
  if ( id == t->Points[0]->InsertionId || id == t->Points[1]->InsertionId ||
       id == t->Points[2]->InsertionId || id == t->Points[3]->InsertionId )
    {
    return 1;
    }
  else
    {
    return 0;
    }
}
