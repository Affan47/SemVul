AnimateSlider(int selectionState)
{

  vtkSliderRepresentation *sliderRep =
    reinterpret_cast<vtkSliderRepresentation*>(this->WidgetRep);


  if ( selectionState == vtkSliderRepresentation::Outside ||
       selectionState == vtkSliderRepresentation::Slider )
    {
    return;
    }


  double minValue=sliderRep->GetMinimumValue();
  double maxValue=sliderRep->GetMaximumValue();
  double pickedT=sliderRep->GetPickedT();

  if ( this->AnimationMode == vtkSliderWidget::Jump )
    {
    if ( selectionState == vtkSliderRepresentation::Tube )
      {
      sliderRep->SetValue(minValue + pickedT*(maxValue-minValue));
      }

    else if ( selectionState == vtkSliderRepresentation::LeftCap )
      {
      sliderRep->SetValue(minValue);
      }

    else if ( selectionState == vtkSliderRepresentation::RightCap )
      {
      sliderRep->SetValue(maxValue);
      }
    sliderRep->BuildRepresentation();
    this->InvokeEvent(vtkCommand::InteractionEvent,NULL);
    }

  else if ( this->AnimationMode == vtkSliderWidget::Animate )
    {
    double targetValue=minValue, originalValue=sliderRep->GetValue();
    if ( selectionState == vtkSliderRepresentation::Tube )
      {
      targetValue = minValue + pickedT*(maxValue-minValue);
      }

    else if ( selectionState == vtkSliderRepresentation::LeftCap )
      {
      targetValue = minValue;
      }

    else if ( selectionState == vtkSliderRepresentation::RightCap )
      {
      targetValue = maxValue;
      }


    double value;
    for (int i=0; i < this->NumberOfAnimationSteps; i++)
      {
      value = originalValue +
        (static_cast<double>(i+1)/this->NumberOfAnimationSteps)*(targetValue-originalValue);
      sliderRep->SetValue(value);
      sliderRep->BuildRepresentation();
      this->InvokeEvent(vtkCommand::InteractionEvent,NULL);
      this->Render();
      }
    }

  this->WidgetState = vtkSliderWidget::Start;
}
