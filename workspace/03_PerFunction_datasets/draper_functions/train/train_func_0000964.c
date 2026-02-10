convertOptLengthSpecC(ELObj *obj, const Identifier *ident,
					const Location &loc,
					FOTBuilder::OptLengthSpec &result)
{
  obj = convertFromString(obj, convertAllowBoolean|convertAllowNumber, loc);
  if (obj == makeFalse()) {
    result.hasLength = 0;
    return 1;
  }
  if (convertLengthSpecC(obj, ident, loc, result.length)) {
    result.hasLength = 1;
    return 1;
  }
  return 0;
}
