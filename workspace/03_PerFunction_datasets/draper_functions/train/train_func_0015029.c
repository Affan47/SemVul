findVertex(GcPoint* point)
{
  BodyElement* vertex = NULL;


  GcPoint* stored_point = this->getPoint(point);


  if ( stored_point != NULL ) {
    vertex = getVertex(stored_point);
  }

  return vertex;
}
