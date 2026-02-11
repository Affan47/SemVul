parseIndicatedReservedName(const AllowedParams &allow,
					   Param &parm)
{
  Syntax::ReservedName rn;
  if (!getIndicatedReservedName(&rn))
    return 0;
  if (!allow.reservedName(rn)) {
    message(ParserMessages::invalidReservedName,
	    StringMessageArg(currentToken()));
    return 0;
  }
  parm.type = Param::indicatedReservedName + rn;
  return 1;
}
