EnumerateProperties (NPIdentifier **_result, uint32_t *_count)
{
  if (!mPropertyNameIdentifiers)
    return false;

  uint32_t bytes = mPropertyNamesCount * sizeof (NPIdentifier);
  NPIdentifier *identifiers = reinterpret_cast<NPIdentifier*>(NPN_MemAlloc (bytes));
  if (!identifiers)
    return false;

  memcpy (identifiers, mPropertyNameIdentifiers, bytes);

  *_result = identifiers;
  *_count = mPropertyNamesCount;

  return true;
}
