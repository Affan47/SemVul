HasMethod (NPIdentifier aName)
{
  if (!IsValid ())
    return false;

  int methodIndex = GetClass()->GetMethodIndex (aName);
  NOTE (g_print ("totemNPObject::HasMethod [%p] %s => %s\n", (void*) this, NPN_UTF8FromIdentifier (aName), methodIndex >= 0 ? "yes" : "no"));
  if (methodIndex >= 0)
    return true;

  if (aName == NPN_GetStringIdentifier ("__noSuchMethod__"))
    return true;

  return false;
}
