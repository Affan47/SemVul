Invalidate (NPObject *aObject)
{
  totemNPObject* object = static_cast<totemNPObject*> (aObject);
  object->Invalidate ();
}
