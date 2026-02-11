GetNextIntersections(
                                         vtkIdList *intersectedCells,
                                         vtkDoubleArray *intersectionLengths,
                                         vtkDataArray *scalars,
                                         vtkDataArray *nearIntersections,
                                         vtkDataArray *farIntersections)
{
  if (intersectedCells)
    {
    intersectedCells->SetNumberOfIds(this->MaxNumberOfIntersections);
    }
  if (intersectionLengths)
    {
    intersectionLengths->SetNumberOfComponents(1);
    intersectionLengths->SetNumberOfTuples(this->MaxNumberOfIntersections);
    }

  vtkIdType numIntersections = 0;

  if (!scalars)
    {
    numIntersections = TemplateCastRay
      ((const float *)NULL, this->RayCastFunction, 0,
       this->RayPosition[0], this->RayPosition[1], this->Bounds[1],
       this->IntersectionPtr, this->CurrentTriangle, this->CurrentTetra,
       (intersectedCells ? intersectedCells->GetPointer(0) : NULL),
       (intersectionLengths ? intersectionLengths->GetPointer(0) : NULL),
       (float *)NULL, (float *)NULL, this->MaxNumberOfIntersections);
    }
  else
    {
    if (   (scalars->GetDataType() != nearIntersections->GetDataType())
        || (scalars->GetDataType() != farIntersections->GetDataType()) )
      {
      vtkErrorMacro(<< "Data types for scalars do not match up.");
      }

    nearIntersections->SetNumberOfComponents(scalars->GetNumberOfComponents());
    nearIntersections->SetNumberOfTuples(this->MaxNumberOfIntersections);
    farIntersections->SetNumberOfComponents(scalars->GetNumberOfComponents());
    farIntersections->SetNumberOfTuples(this->MaxNumberOfIntersections);

    switch (scalars->GetDataType())
      {
      vtkTemplateMacro
        (numIntersections = TemplateCastRay
         ((const VTK_TT *)scalars->GetVoidPointer(0),
          this->RayCastFunction, scalars->GetNumberOfComponents(),
          this->RayPosition[0], this->RayPosition[1], this->Bounds[1],
          this->IntersectionPtr, this->CurrentTriangle, this->CurrentTetra,
          (intersectedCells ? intersectedCells->GetPointer(0) : NULL),
          (intersectionLengths ? intersectionLengths->GetPointer(0) : NULL),
          (VTK_TT *)nearIntersections->GetVoidPointer(0),
          (VTK_TT *)farIntersections->GetVoidPointer(0),
          this->MaxNumberOfIntersections));
      }

    nearIntersections->SetNumberOfTuples(numIntersections);
    farIntersections->SetNumberOfTuples(numIntersections);
    }

  if (intersectedCells)
    {
    intersectedCells->SetNumberOfIds(numIntersections);
    }
  if (intersectionLengths)
    {
    intersectionLengths->SetNumberOfTuples(numIntersections);
    }

  return numIntersections;
}
