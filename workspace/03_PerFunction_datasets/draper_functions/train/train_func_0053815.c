SetCellId( vtkIdType cell )
{
  if ( cell == this->CurrentCellId )
    return;

  this->CurrentCellId = cell;

  if ( this->CurrentMesh )
    this->CurrentCellData = this->CurrentMesh->GetCell( this->CurrentCellId );

  this->Modified();
}
