procParamValue(parseUnion * lvalp, ParserControl * parm)
{
   static XmlElement elm[] = {
      {"NAME"},
      {"PARAMTYPE"},
      {"EMBEDDEDOBJECT"},
      {NULL}
   };
   XmlAttr attr[3];
   int i, m;

   memset(attr, 0, sizeof(attr));
   if (tagEquals(parm->xmb, "PARAMVALUE")) {
      if (attrsOk(parm->xmb, elm, attr, "PARAMVALUE", ZTOK_PARAMVALUE)) {
         lvalp->xtokParamValue.name = attr[0].attr;
         lvalp->xtokParamValue.type = CMPI_null;
         if (attr[1].attr) {
            lvalp->xtokParamValue.type = xmlToCmpiType(attr[1].attr);
         }
         return XTOK_PARAMVALUE;
      }
   }
   return 0;
}
