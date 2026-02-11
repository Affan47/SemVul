GetColor(double x,
                                                               double c[4])
{
  unsigned int i = 1;
  unsigned int size = static_cast<unsigned int>(this->ControlPoints.size());
  if( !size )
    {
      c[0] = 0.0;
      c[1] = 0.0;
      c[2] = 0.0;
      c[3] = 0.0;
    return;
    }
  while (this->ControlPoints[i] < x && i < size-1)
    {
    i++;
    }

  double before = this->ControlPoints[i-1];
  double after = this->ControlPoints[i];

  double interp = (x-before)/(after-before);

  double *beforec = this->Colors[i-1].c;
  double *afterc = this->Colors[i].c;
  c[0] = (1-interp)*beforec[0] + interp*afterc[0];
  c[1] = (1-interp)*beforec[1] + interp*afterc[1];
  c[2] = (1-interp)*beforec[2] + interp*afterc[2];
  c[3] = (1-interp)*beforec[3] + interp*afterc[3];
}
