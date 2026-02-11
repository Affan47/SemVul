readVertex(char* s)
{
  static Point3 point;
  static GcPoint gpoint;


  if ( !readPoint(s, point) )
    return NULL;

  gpoint.setPosit(point[0], point[1], point[2]);

  BodyElement* vertex = new BodyElement1D(&gpoint);

  return vertex;
}
