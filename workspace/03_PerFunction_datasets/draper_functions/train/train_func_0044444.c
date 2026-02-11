SetCursor(int cState)
{
  if(!this->Resizable && cState != vtkBorderRepresentation::Inside)
    {
    this->RequestCursorShape(VTK_CURSOR_DEFAULT);
    return;
    }

  switch (cState)
    {
    case vtkBorderRepresentation::AdjustingP0:
      this->RequestCursorShape(VTK_CURSOR_SIZESW);
      break;
    case vtkBorderRepresentation::AdjustingP1:
      this->RequestCursorShape(VTK_CURSOR_SIZESE);
      break;
    case vtkBorderRepresentation::AdjustingP2:
      this->RequestCursorShape(VTK_CURSOR_SIZENE);
      break;
    case vtkBorderRepresentation::AdjustingP3:
      this->RequestCursorShape(VTK_CURSOR_SIZENW);
      break;
    case vtkBorderRepresentation::AdjustingE0:
    case vtkBorderRepresentation::AdjustingE2:
      this->RequestCursorShape(VTK_CURSOR_SIZENS);
      break;
    case vtkBorderRepresentation::AdjustingE1:
    case vtkBorderRepresentation::AdjustingE3:
      this->RequestCursorShape(VTK_CURSOR_SIZEWE);
      break;
    case vtkBorderRepresentation::Inside:
      if ( reinterpret_cast<vtkBorderRepresentation*>(this->WidgetRep)->GetMoving() )
        {
        this->RequestCursorShape(VTK_CURSOR_SIZEALL);
        }
      else
        {
        this->RequestCursorShape(VTK_CURSOR_HAND);
        }
      break;
    default:
      this->RequestCursorShape(VTK_CURSOR_DEFAULT);
    }
}
