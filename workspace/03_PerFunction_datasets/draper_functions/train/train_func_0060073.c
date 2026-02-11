val_int()
{
  DBUG_ASSERT(fixed == 1);
  null_value= 0;
  return (longlong) args[0]->collation.derivation;
}
