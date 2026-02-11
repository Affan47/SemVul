GetReslicePlane()
{

  if (vtkResliceCursorRepresentation *rep =
      vtkResliceCursorRepresentation::SafeDownCast(
        this->ResliceCursorWidget->GetRepresentation()))
    {
    const int planeOrientation =
      rep->GetCursorAlgorithm()->GetReslicePlaneNormal();
    vtkPlane *plane = this->GetResliceCursor()->GetPlane(planeOrientation);
    return plane;
    }

  return NULL;
}
