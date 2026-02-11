UpdateShiftScale()
{
  int gridType = this->GridScalarType;


  if (gridType == VTK_DOUBLE || gridType == VTK_DOUBLE)
    {
    this->DisplacementShift = 0.0;
    this->DisplacementScale = 1.0;
    vtkDebugMacro(<< "displacement (scale, shift) = (" <<
                  this->DisplacementScale << ", " <<
                  this->DisplacementShift << ")");
    return;
    }


  if (this->ShiftScaleTime.GetMTime() > this->GetMTime())
    {
    return;
    }


  double minDisplacement, maxDisplacement;
  vtkTransformToGridMinMax(this,this->GridExtent,
                           minDisplacement,
                           maxDisplacement);

  vtkDebugMacro(<< "displacement (min, max) = (" <<
                minDisplacement << ", " << maxDisplacement << ")");

  double typeMin,typeMax;

  switch (gridType)
    {
    case VTK_SHORT:
      typeMin = VTK_SHORT_MIN;
      typeMax = VTK_SHORT_MAX;
      break;
    case VTK_UNSIGNED_SHORT:
      typeMin = VTK_UNSIGNED_SHORT_MIN;
      typeMax = VTK_UNSIGNED_SHORT_MAX;
      break;
    case VTK_CHAR:
      typeMin = VTK_CHAR_MIN;
      typeMax = VTK_CHAR_MAX;
      break;
    case VTK_UNSIGNED_CHAR:
      typeMin = VTK_UNSIGNED_CHAR_MIN;
      typeMax = VTK_UNSIGNED_CHAR_MAX;
      break;
    default:
      vtkErrorMacro(<< "UpdateShiftScale: Unknown input ScalarType");
      return;
    }

  this->DisplacementScale = ((maxDisplacement - minDisplacement)/
                             (typeMax - typeMin));
  this->DisplacementShift = ((typeMax*minDisplacement-typeMin*maxDisplacement)/
                             (typeMax - typeMin));

  if (this->DisplacementScale == 0.0)
    {
    this->DisplacementScale = 1.0;
    }

  vtkDebugMacro(<< "displacement (scale, shift) = (" <<
                this->DisplacementScale << ", " <<
                this->DisplacementShift << ")");

  this->ShiftScaleTime.Modified();
}
