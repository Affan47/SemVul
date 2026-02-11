positionRelativeToCursor( const Cursor & cursor ) const
{
  if (end() <= cursor)
    return -1;

  if (start() > cursor)
    return +1;

  return 0;
}
