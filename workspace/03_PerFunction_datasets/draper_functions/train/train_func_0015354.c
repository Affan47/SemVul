addElement(int layer, BodyElement* be)
{
  if (!checkLayerIndex(layer)) return 0;

  BodyElementTable* elements = belements[layer];

  RangeVector rv;

  (*elements)[be->Id()] = be;

  nofElements[layer]++;

  if ( !be->getRangeVector(rv) )
    return 0;

  updateBoundBox(layer, rv);

  return 0;
}
