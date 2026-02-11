procProperty(parseUnion * lvalp, ParserControl * parm)
{
   static XmlElement elm[] = { {"NAME"},
   {"TYPE"},
   {"CLASSORIGIN"},
   {"PROPAGATED"},
   {"EMBEDDEDOBJECT"},
   {NULL}
   };
   XmlAttr attr[5];
   int i, m;

   memset(attr, 0, sizeof(attr));
   if (tagEquals(parm->xmb, "PROPERTY")) {
      attr[1].attr = NULL;
      lvalp->xtokProperty.valueType = (CMPIType) 1;
      if (attrsOk(parm->xmb, elm, attr, "PROPERTY", ZTOK_PROPERTY)) {
         memset(&lvalp->xtokProperty, 0, sizeof(XtokProperty));
         lvalp->xtokProperty.name = attr[0].attr;
         lvalp->xtokProperty.valueType = CMPI_null;
         if (attr[1].attr)
            lvalp->xtokProperty.valueType = xmlToCmpiType(attr[1].attr);
         lvalp->xtokProperty.classOrigin = attr[2].attr;
         if (attr[3].attr)
            lvalp->xtokProperty.propagated = !strcasecmp(attr[3].attr, "true");
         lvalp->xtokProperty.propType = typeProperty_Value;
         return XTOK_PROPERTY;
      }
   }
   return 0;
}
