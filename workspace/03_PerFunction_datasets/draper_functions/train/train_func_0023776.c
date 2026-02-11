GetFaces(vtkIdType cellId)
{

  vtkIdType loc;
  if ( !this->Faces ||
       cellId < 0 || cellId > this->FaceLocations->GetMaxId() ||
       (loc=this->FaceLocations->GetValue(cellId)) == -1 )
    {
    return NULL;
    }

  return this->Faces->GetPointer(loc);
}
