IsItemOnReslicedPlane( vtkAbstractWidget * w )
{

  if (vtkDistanceWidget *dw = vtkDistanceWidget::SafeDownCast( w ))
    {
    return this->IsWidgetOnReslicedPlane(dw);
    }
  if (vtkAngleWidget *aw = vtkAngleWidget::SafeDownCast( w ))
    {
    return this->IsWidgetOnReslicedPlane(aw);
    }
  if (vtkBiDimensionalWidget *aw = vtkBiDimensionalWidget::SafeDownCast( w ))
    {
    return this->IsWidgetOnReslicedPlane(aw);
    }
  if (vtkCaptionWidget *capw = vtkCaptionWidget::SafeDownCast( w ))
    {
    return this->IsWidgetOnReslicedPlane(capw);
    }
  if (vtkContourWidget *capw = vtkContourWidget::SafeDownCast( w ))
    {
    return this->IsWidgetOnReslicedPlane(capw);
    }
  if (vtkSeedWidget *s = vtkSeedWidget::SafeDownCast( w ))
    {
    return this->IsWidgetOnReslicedPlane(s);
    }
  if (vtkHandleWidget *s = vtkHandleWidget::SafeDownCast( w ))
    {
    return this->IsWidgetOnReslicedPlane(s);
    }

  return true;
}
