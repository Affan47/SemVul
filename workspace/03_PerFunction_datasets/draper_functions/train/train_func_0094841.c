internalEntityInfo(const InternalEntity *entity)
{
  if (!entity)
    return;
  os() << '#'
       << char(entity->dataType() == Entity::cdata ? 'C' : 'S')
       << "DATA-INTERNAL" << nl;
  const StringC &str = entity->string();
  lines(markupLine, str.data(), str.size());
  flushLine(markupLine);
}
