getElementGroupType() const
{
  BodyElementGroup* beg = model->getBodyElementGroupById(elementGroupId);

  if ( beg == NULL ) return NONE_GROUP;

  return beg->getGroupType();
}
