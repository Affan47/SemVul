ReadNumberOfPoints(vtkIdType *numPoints)
{
  int status = this->ParseIdValue(numPoints);

  if (status != 0)
    {
    if (*numPoints < 0)
      {

      vtkErrorMacro("Bad number of points -> " << *numPoints << " "
                    << this->FileName << ":" << this->LineNumber);
      status = 0;
      }
    else if (*numPoints > VTK_LARGE_ID/4)
      {
      vtkErrorMacro("Too many points -> " << *numPoints << " "
                    << this->FileName << ":" << this->LineNumber);
      status = 0;
      }
    }

  return status;
}
