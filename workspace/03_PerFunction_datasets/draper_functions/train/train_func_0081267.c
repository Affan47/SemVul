SetLensAngle(double angle)
{
  if (angle >= 0.0 && angle <= 90)
  {
    if (this->Initialized)
    {
      this->Camera->Roll(-this->Roll);
      this->Camera->Pitch(this->LensAngle);

      this->LensAngle = angle;
      this->Camera->Pitch(-this->LensAngle);
      this->Camera->Roll(this->Roll);
    }
    else
    {
      this->LensAngle = angle;
    }
  }
}
