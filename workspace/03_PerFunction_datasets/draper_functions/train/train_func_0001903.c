SetEnabled( int enabling )
{


  if ( enabling )
    {
    if ( this->WidgetState == vtkContourWidget::Start )
      {
      reinterpret_cast<vtkContourRepresentation*>(this->WidgetRep)->VisibilityOff();
      }
    else
      {
      reinterpret_cast<vtkContourRepresentation*>(this->WidgetRep)->VisibilityOn();
      }
    }

  this->Superclass::SetEnabled( enabling );
}
