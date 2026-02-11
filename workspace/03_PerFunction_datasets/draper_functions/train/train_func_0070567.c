decVRot(float decVal)
{
  vAngle -= decVal;

  if (vAngle < 0)
    vAngle += 360;
}
