DeepCopy(vtkDataObject *dataObject)
{


  this->vtkPointSet::DeepCopy(dataObject);

  vtkPolyData *polyData = vtkPolyData::SafeDownCast(dataObject);

  if ( polyData != NULL )
    {
    vtkCellArray *ca;
    ca = vtkCellArray::New();
    ca->DeepCopy(polyData->GetVerts());
    this->SetVerts(ca);
    ca->Delete();

    ca = vtkCellArray::New();
    ca->DeepCopy(polyData->GetLines());
    this->SetLines(ca);
    ca->Delete();

    ca = vtkCellArray::New();
    ca->DeepCopy(polyData->GetPolys());
    this->SetPolys(ca);
    ca->Delete();

    ca = vtkCellArray::New();
    ca->DeepCopy(polyData->GetStrips());
    this->SetStrips(ca);
    ca->Delete();

    if ( this->Cells )
      {
      this->Cells->UnRegister(this);
      this->Cells = NULL;
      }
    if (polyData->Cells)
      {
      this->BuildCells();
      }

    if ( this->Links )
      {
      this->Links->UnRegister(this);
      this->Links = NULL;
      }
    if (polyData->Links)
      {
      this->BuildLinks();
      }
    }
}
