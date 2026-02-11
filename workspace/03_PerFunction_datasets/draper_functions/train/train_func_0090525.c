isectionsWithYdir(GcPoint* ydir_startp, int& nof_values , double*& values)
{
  nof_values = 0;


  double px = ydir_startp->Pos(X);
  double py = ydir_startp->Pos(Y);


  if ( isGreater(px, data.center[0] + data.radius) ||
       isLess(px, data.center[0] - data.radius)
     ) {
    return;
  }

  values = new double[2];


  double u1 = acos( (px - data.center[0]) / data.radius );
  double u2 = -u1;


  if ( !isLess(u1, data.start_u) || !isGreater(u1, data.end_u) ) {
    values[nof_values++] = data.center[1] + data.radius * sin(u1);
  }

  if ( !isLess(u2, data.start_u) || !isGreater(u2, data.end_u) ) {
    values[nof_values++] = data.center[1] + data.radius * sin(u2);
  }
}
