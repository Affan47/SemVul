findTextNext( bool reverse )
{
  if (parentPart())
      return parentPart()->findTextNext( reverse );
  return d->m_find.findTextNext( reverse );
}
