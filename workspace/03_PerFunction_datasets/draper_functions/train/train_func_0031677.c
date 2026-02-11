addToElementGroup(BodyElement* be, int group_tag)
{
  objectType ot = OT_ELEMENT_GROUP;
  objectType bt = be->getObjectType();

  BodyElementGroup* beg = (BodyElementGroup*)getModelObjectByTag(ot, group_tag);

  if ( beg == NULL ) {
    beg = new BodyElementGroup();
    beg->setObjectType(ot);
    beg->setElementType(bt);
  }

  beg->addElement(be->Id());

  return beg->Id();
}
