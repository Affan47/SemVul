procMethodResp(parseUnion * lvalp, ParserControl * parm)
{
   static XmlElement elm[] = {
      {"NAME"},
      {NULL}
   };
   XmlAttr attr[1];

   memset(attr, 0, sizeof(attr));
   if (tagEquals(parm->xmb, "METHODRESPONSE")) {
      if (attrsOk(parm->xmb, elm, attr, "METHODRESPONSE", ZTOK_METHODRESP)) {
         memset(&lvalp->xtokMethodRespContent, 0, sizeof(XtokMethodRespContent));
         lvalp->xtokMethodRespContent.name = attr[0].attr;
         parm->respHdr.id = attr[0].attr;
         return XTOK_METHODRESP;
      }
   }

   return 0;
}
