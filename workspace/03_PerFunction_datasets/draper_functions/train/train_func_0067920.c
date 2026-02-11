GetAlignmentPoint()
{
  int alignmentCode = 0;

  if ( ! this->TextProperty)
    {
    return 0;
    }
  switch (this->TextProperty->GetJustification())
    {
    case VTK_TEXT_LEFT:
      alignmentCode = 0;
      break;
    case VTK_TEXT_CENTERED:
      alignmentCode = 1;
      break;
    case VTK_TEXT_RIGHT:
      alignmentCode = 2;
      break;
    default:
      vtkErrorMacro(<<"Unknown justifaction code.");
    }
   switch (this->TextProperty->GetVerticalJustification())
    {
    case VTK_TEXT_BOTTOM:
      alignmentCode += 0;
      break;
    case VTK_TEXT_CENTERED:
      alignmentCode += 3;
      break;
    case VTK_TEXT_TOP:
      alignmentCode += 6;
      break;
    default:
      vtkErrorMacro(<<"Unknown justifaction code.");
    }
  return alignmentCode;
}
