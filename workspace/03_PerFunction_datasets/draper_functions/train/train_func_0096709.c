set_conf_double(
lList **alpp,
lList **clpp,
int fields[],
const char *key,
lListElem *ep,
int name_nm,
int operation_nm
) {
   const char *str;
   double dval;

   DENTER(CULL_LAYER, "set_conf_double");

   if(!(str=get_conf_value(fields?NULL:alpp, *clpp, CF_name, CF_value, key))) {
      DEXIT;
      return fields?true:false;
   }


   if (operation_nm) {
      while (isspace((int) *str))
         str++;
      switch (*str) {
         case '+':
            lSetUlong(ep, operation_nm, MODE_ADD);
            str++;
            break;
         case '-':
            lSetUlong(ep, operation_nm, MODE_SUB);
            str++;
            break;
         case '=':
            lSetUlong(ep, operation_nm, MODE_SET);
            str++;
            break;
         default:
            lSetUlong(ep, operation_nm, MODE_RELATIVE);
      }
   }

   if ( (sscanf(str, "%lf", &dval)!=1) || ( strncasecmp(str,"inf",3) == 0 ) ) {
      SGE_ADD_MSG_ID(sprintf(SGE_EVENT, MSG_GDI_CONFIGARGUMENTNOTDOUBLE_SS ,
               key, str));
      answer_list_add(alpp, SGE_EVENT, STATUS_ESYNTAX, ANSWER_QUALITY_ERROR);
      DEXIT;
      return false;
   }

   lSetDouble(ep, name_nm, dval);
   lDelElemStr(clpp, CF_name, key);
   add_nm_to_set(fields, name_nm);

   DEXIT;
   return true;
}
