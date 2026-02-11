EvaluateCellDataField( double* result, double* vtkNotUsed(weights), int field )
{


  vtkDataArray* array = this->CurrentMesh->GetCellData()->GetArray( field );
  int nc = array->GetNumberOfComponents();
  int j;
  double* tuple = array->GetTuple( this->CurrentCellId );
  for ( j=0; j<nc; ++j )
    result[j] = tuple[j];
}
