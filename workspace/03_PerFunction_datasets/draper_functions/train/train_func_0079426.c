GetFaceStream(vtkIdType cellId, vtkIdType& nfaces,
                                        vtkIdType* &ptIds)
{
  if (this->GetCellType(cellId) != VTK_POLYHEDRON)
    {
    this->GetCellPoints(cellId, nfaces, ptIds);
    return;
    }

  if (!this->Faces || !this->FaceLocations)
    {
    return;
    }

  vtkIdType loc = this->FaceLocations->GetValue(cellId);
  vtkIdType* facePtr = this->Faces->GetPointer(loc);

  nfaces = *facePtr;
  ptIds = facePtr+1;
}
