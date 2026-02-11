contains (const Pt3D& point) const
{

  if ( fabs (normal.X() * point.x + normal.Y() * point.y + normal.Z() * point.z - Deq) >= DOUBLE_TOLERANCE )
  {
    return false;
  }


  return (containedBetweenLines (point, vertices[0], vertices[3],
                            vertices[1], vertices[2]) ) ?
                            containedBetweenLines (point, vertices[0],                                                    vertices[1], vertices[3],
                                             vertices[2]) : false;
}
