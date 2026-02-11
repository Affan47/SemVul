getBodyElementGroupById(int id) const
{
  ModelObject* obj = getModelObjectById(id);

  if ( obj == NULL ) return NULL;

  objectType ot = obj->getObjectType();

  if ( OT_ELEMENT_GROUP != obj->getObjectType() ) return NULL;

  return (BodyElementGroup*)obj;
}
