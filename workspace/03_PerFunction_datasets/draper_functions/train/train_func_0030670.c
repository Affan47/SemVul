updateGeometry()
{
  IdList vertex_tags;

  if ( ptrGmtr != NULL ) {
    if ( !ptrGmtr->updateGeometry(tag, vertex_tags) ) return false;
  }

  update();

  return true;
}
