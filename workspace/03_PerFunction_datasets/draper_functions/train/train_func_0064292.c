getFunctionName(std::string datatype){
  std::string ret;
  if (datatype ==  DateTimeAttribute::getIdentifier()) ret = NAME_TIME_IN_RANGE;
  else if (datatype ==  StringAttribute::getIdentifier()) ret = NAME_STRING_IN_RANGE;
  return ret;
}
