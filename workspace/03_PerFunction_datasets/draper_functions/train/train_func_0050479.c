attributeEntity(const StartElementEvent &event,
				       const char *attName)
{
  const AttributeList &atts = event.attributes();
  StringC attNameString;
  for (const char *p = attName; *p; p++)
    attNameString += Char(*p);
  unsigned index;
  if (!atts.attributeIndex(attNameString, index))
    return 0;
  const AttributeSemantics *sem = atts.semantics(index);
  if (!sem || sem->nEntities() != 1)
    return 0;
  return sem->entity(0);
}
