setuserattr(Arrayinfo ap, Field f, char *compname)
{
  int i, attr_count=0;
  int alen;
  nc_type datatype;
  Type type;
  Array a;
  char *attr_string;
  void *attr_value;

  while(ncattname(ap->cdfhandle,ap->varid,attr_count,ap->stringattr) !=-1) {
    attr_count++;

    for (i=0; i<MAX_DXATTRIBUTES; i++){
      if (!strcmp(dxattributes[i],ap->stringattr))
	break;
    }
    if (i < MAX_DXATTRIBUTES)
      continue;

    if(ncattinq(ap->cdfhandle, ap->varid, ap->stringattr, &datatype, &alen) < 0)
	return ERROR;


    switch(datatype) {
      case NC_CHAR:   type = TYPE_STRING; break;
      case NC_SHORT:  type = TYPE_SHORT;  break;
      case NC_LONG:   type = TYPE_INT;    break;
      case NC_FLOAT:  type = TYPE_FLOAT;  break;
      case NC_DOUBLE: type = TYPE_DOUBLE; break;
      default:        type = TYPE_UBYTE;  break;

    }

    if (type == TYPE_STRING){
      attr_string = (char *)DXAllocate(alen+1);
      if (ncattget(ap->cdfhandle, ap->varid,ap->stringattr,attr_string) < 0)
        return ERROR;
      attr_string[alen] = '\0';
      DXSetComponentAttribute(f, compname, ap->stringattr, STR(attr_string));
      DXFree((Pointer)attr_string);
    }
    else{
      a = DXNewArray(type,CATEGORY_REAL,0);
      a = DXAddArrayData(a,0,alen,NULL);
      attr_value = DXGetArrayData(a);
      if (ncattget(ap->cdfhandle, ap->varid,ap->stringattr,attr_value) < 0)
        return ERROR;
      DXSetComponentAttribute(f,compname, ap->stringattr, (Object)a);
    }
  }
  return OK;
}
