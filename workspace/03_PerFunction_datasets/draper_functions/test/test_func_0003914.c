GWEN_XMLNode_FindTag(const GWEN_XMLNODE *n,
                                   const char *tname,
                                   const char *pname,
                                   const char *pvalue){
  while(n) {
    if (-1!=GWEN_Text_ComparePattern(n->data, tname, 0)) {
      if (pname) {
        const char *p;

        p=GWEN_XMLNode_GetProperty(n, pname, 0);
        if (p) {
          if (!pvalue)
            return (GWEN_XMLNODE*)n;
          if (-1!=GWEN_Text_ComparePattern(pvalue, p, 0))
            return (GWEN_XMLNODE*)n;
        }
        else {

          if (!pvalue)
            return (GWEN_XMLNODE*)n;
        }
      }
      else
        return (GWEN_XMLNODE*)n;
    }
    n=GWEN_XMLNode_GetNextTag(n);
  }
  return 0;
}
