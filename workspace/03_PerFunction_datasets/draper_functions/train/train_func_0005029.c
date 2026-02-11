IntersectEllipse(double vector[3], double v[3])
{
  double a = vector[0];
  double b = vector[1];
  double c = vector[2];

  double num = a*a * b*b * c*c;
  double den = v[0]*v[0]*b*b*c*c + v[1]*v[1]*a*a*c*c + v[2]*v[2]*a*a*b*b;

  if ( den <= 0.0 )
    {
    return 0.0;
    }
  else
    {
    return sqrt(num/den);
    }
}
