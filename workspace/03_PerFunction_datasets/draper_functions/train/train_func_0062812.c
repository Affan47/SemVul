unmarshalReturnedValues(cdrStream& _n)
{
  result = new CosTradingRepos::ServiceTypeRepository::TypeStruct;
  (CosTradingRepos::ServiceTypeRepository::TypeStruct&)result <<= _n;

}
