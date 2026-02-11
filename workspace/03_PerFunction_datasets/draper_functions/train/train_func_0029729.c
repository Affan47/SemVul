set_conf_string(
lList **alpp,
lList **clpp,
int fields[],
const char *key,
lListElem *ep,
int name_nm
) {
   const char *str;
   int pos;
   int dataType;

   DENTER(TOP_LAYER, "set_conf_string");

   if(!(str=get_conf_value(fields?NULL:alpp, *clpp, CF_name, CF_value, key))) {
      DEXIT;
      return fields?true:false;
   }

   pos = lGetPosViaElem(ep, name_nm, SGE_NO_ABORT);
   dataType = lGetPosType(lGetElemDescr(ep),pos);
   switch (dataType) {
      case lStringT:
         DPRINTF(("set_conf_string: lStringT data type (Type: %s)\n",lNm2Str(name_nm)));
         lSetString(ep, name_nm, str);
         break;
      case lHostT:
         DPRINTF(("set_conf_string: lHostT data type (Type: %s)\n",lNm2Str(name_nm)));
         lSetHost(ep, name_nm, str);
         break;
      default:
         DPRINTF(("!!!!!!!!!set_conf_string: unexpected data type !!!!!!!!!!!!!!!!!\n"));
         break;
   }
   lDelElemStr(clpp, CF_name, key);
   add_nm_to_set(fields, name_nm);

   DEXIT;
   return true;
}
