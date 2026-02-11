gamgi_engine_find_object (gamgi_object *object,
gamgi_object *parent)
{
gamgi_bond *bond;
int class = parent->class;


if (class == GAMGI_ENGINE_GAMGI) return TRUE;


do
  {
  if (object == parent) return TRUE;
  if (object->class == GAMGI_ENGINE_BOND)
    {
    bond = GAMGI_CAST_BOND object;
    if (gamgi_engine_find_object (GAMGI_CAST_OBJECT
    bond->atom1, parent) == TRUE) return TRUE;
    if (gamgi_engine_find_object (GAMGI_CAST_OBJECT
    bond->atom2, parent) == TRUE) return TRUE;
    return FALSE;
    }
  else object = object->object;
  } while (object != NULL && object->class <= class);

return FALSE;
}
