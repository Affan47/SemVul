InsertNextCell(int type, vtkIdType npts,
                                              vtkIdType *ptIds)
{
  if (type != VTK_POLYHEDRON)
    {

    this->Connectivity->InsertNextCell(npts,ptIds);

    vtkDebugMacro(<< "insert location "
                  << this->Connectivity->GetInsertLocation(npts));
    this->Locations->InsertNextValue(
      this->Connectivity->GetInsertLocation(npts));


    if ( this->FaceLocations )
      {
      this->FaceLocations->InsertNextValue(-1);
      }
    }
  else
    {


    vtkIdType realnpts;


    if ( ! this->Faces )
      {
      this->Faces = vtkIdTypeArray::New();
      this->Faces->Allocate(this->Types->GetSize());
      this->FaceLocations = vtkIdTypeArray::New();
      this->FaceLocations->Allocate(this->Types->GetSize());

      for(vtkIdType i = 0; i <= this->Types->GetMaxId(); i++)
        {
        this->FaceLocations->InsertNextValue(-1);
        }
      }


    this->Locations->InsertNextValue(this->Connectivity->GetData()->GetMaxId()+1);

    this->FaceLocations->InsertNextValue(this->Faces->GetMaxId()+1);

    vtkUnstructuredGrid::DecomposeAPolyhedronCell(
        npts, ptIds, realnpts, this->Connectivity, this->Faces);
    }

  return this->Types->InsertNextValue(static_cast<unsigned char>(type));
}
