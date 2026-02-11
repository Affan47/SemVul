PrintSelf(ostream& os, vtkIndent indent)
{

  this->Superclass::PrintSelf(os,indent);

  os << indent << "Animation Mode: ";
  switch ( this->AnimationMode )
    {
    case vtkSliderWidget::Jump:
      os << "Jump\n";
      break;
    case vtkSliderWidget::Animate:
      os << "Animate\n";
      break;
    default:
      os << "AnimateOff\n";
    }

  os << indent << "Number of Animation Steps: "
     << this->NumberOfAnimationSteps << "\n";
}
