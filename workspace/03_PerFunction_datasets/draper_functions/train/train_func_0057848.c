MIBgetnext(VarBindList *list, PDUInt *status, AsnInt *offset)
{
  VarBind *varbind;
  Variable *var;
  AsnOidResult result;

  *offset = 1;
  FOR_EACH_LIST_ELMT(varbind, list)
  {


    var = variables;
    while(var->name != NULL)
    {
      result = AsnOidCompare(var->name, &varbind->name);
      if(var->getnext == NULL)
      {
	if(result == AsnOidGreater)
	  break;
      } else if(result != AsnOidLess)
	break;
      var++;
    }


    for(*status = NOSUCHNAME;
	var->name != NULL && *status == NOSUCHNAME;
	var++)
      if(var->getnext == NULL)
      {
	varbind->name.octs = Asn1Alloc(var->name->octetLen);
	AsnOidCopy(&varbind->name, var->name);
	*status = var->get(varbind, var);
      }
      else
	*status = var->getnext(varbind, var);


    if(*status != NOERROR)
      return;

    (*offset)++;
  }
  *offset = 0;
  return;
}
