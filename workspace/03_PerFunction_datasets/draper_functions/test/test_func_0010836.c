isectionsWithXdir(GcPoint* xdir_startp, bool& negative_on_left)
{


  negative_on_left = false;


  double csx = xdir_startp->Pos(X);
  double csy = xdir_startp->Pos(Y);
  double csz = xdir_startp->Pos(Z);


  double clx = data.start->Pos(X);
  double cly = data.start->Pos(Y);
  double clz = data.start->Pos(Z);


  double klx = data.dir->Pos(X);
  double kly = data.dir->Pos(Y);
  double klz = data.dir->Pos(Z);


  if ( ( klx < -EPSILON || klx > EPSILON) &&
       ( kly > -EPSILON && kly < EPSILON)
     ) {
    return NULL;
  }


  double w;
  if ( kly != 0 ) {
    w = (csy - cly) / kly;
  } else {
    w = 0.0;
  }


  if (w < -EPSILON || w > 1+EPSILON) return NULL;


  double t = (clx - csx) + klx * w;

  if (t < -EPSILON ) return NULL;

  RayHit* result = new RayHit;

  Point3* p = new Point3[1];
  (*p)[0] = clx + klx * w;
  (*p)[1] = cly + kly * w;
  (*p)[2] = clz + klz * w;

  result->count = 1;
  result->points.push_back(p);
  result->min_value = csx + t;

  negative_on_left = kly > 0;

  return result;
}
