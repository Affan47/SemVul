Yaw(double angle)
{
  if (angle - this->YawAngle != 0)
  {
    this->UpdateTool(this->PitchAngle, angle, this->RollAngle);
  }
}
