GetCoordDim(IOM_BASKET model, IOM_OBJECT typeobj) {
  unsigned int dim = 0;

  IOM_ITERATOR modelelei=iom_iteratorobject(model);
  IOM_OBJECT modelele=iom_nextobject(modelelei);
  while(modelele){
    const char *tag=iom_getobjecttag(modelele);
    if (tag && EQUAL(tag,"iom04.metamodel.NumericType")) {
      if (GetAttrObj(model, modelele, "coordType") == typeobj) {
        unsigned int orderpos = GetAttrObjPos(modelele, "coordType");
        if (orderpos > dim) dim = orderpos;
      }
    }
    iom_releaseobject(modelele);
    modelele=iom_nextobject(modelelei);
  }
  iom_releaseiterator(modelelei);

  return dim;
}
