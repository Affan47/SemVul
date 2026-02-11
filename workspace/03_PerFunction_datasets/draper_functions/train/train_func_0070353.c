cols()
{
  DBUG_ASSERT(unit->is_prepared());
  return unit->types.elements;
}
