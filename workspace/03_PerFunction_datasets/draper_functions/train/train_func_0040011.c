insert(int i, TSelect select, int layer, Object *obj)
{
  iObjects.insert(iObjects.begin() + i, SObject());
  SObject &s = iObjects[i];
  s.iSelect = select;
  s.iLayer = layer;
  s.iObject = obj;
}
