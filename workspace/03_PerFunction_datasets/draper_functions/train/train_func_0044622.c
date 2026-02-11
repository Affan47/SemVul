retrieveBackgroundColor(const RenderObject *obj)
{
  QColor result;
  while (!obj->isCanvas()) {
    result = obj->style()->backgroundColor();
    if (result.isValid()) return result;

    obj = obj->container();
  }


  return obj->style()->palette().color( QPalette::Active, QPalette::Base );
}
