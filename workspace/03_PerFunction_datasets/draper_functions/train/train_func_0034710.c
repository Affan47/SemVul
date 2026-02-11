convertOptPositiveIntegerC(ELObj *obj, const Identifier *ident, const Location &loc,
					     long &result)
{
  obj = convertFromString(obj, convertAllowNumber|convertAllowBoolean, loc);
  if (obj == makeFalse()) {
    result = 0;
    return 1;
  }
  if (obj->exactIntegerValue(result) && result > 0)
    return 1;

  invalidCharacteristicValue(ident, loc);
  return 0;
}
