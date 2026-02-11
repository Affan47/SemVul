MIBdelete(AsnOid *oid)
{
  Variable *var;
  void *value;
  AsnOidResult result;


    var = variables;
    while(var->name != NULL)
    {
      result = AsnOidCompare(var->name, oid);
      if(result != AsnOidLess)
	break;
      var++;
    }


  if(result != AsnOidEqual)
    return NULL;

  value = var->value;
  var->value = NULL;

  return value;
}
