sqliteJoinType(Parse *pParse, Token *pA, Token *pB, Token *pC){
  int jointype = 0;
  Token *apAll[3];
  Token *p;
  static struct {
    const char *zKeyword;
    int nChar;
    int code;
  } keywords[] = {
    { "natural", 7, JT_NATURAL },
    { "left",    4, JT_LEFT|JT_OUTER },
    { "right",   5, JT_RIGHT|JT_OUTER },
    { "full",    4, JT_LEFT|JT_RIGHT|JT_OUTER },
    { "outer",   5, JT_OUTER },
    { "inner",   5, JT_INNER },
    { "cross",   5, JT_INNER },
  };
  int i, j;
  apAll[0] = pA;
  apAll[1] = pB;
  apAll[2] = pC;
  for(i=0; i<3 && apAll[i]; i++){
    p = apAll[i];
    for(j=0; j<sizeof(keywords)/sizeof(keywords[0]); j++){
      if( p->n==keywords[j].nChar
          && sqliteStrNICmp(p->z, keywords[j].zKeyword, p->n)==0 ){
        jointype |= keywords[j].code;
        break;
      }
    }
    if( j>=sizeof(keywords)/sizeof(keywords[0]) ){
      jointype |= JT_ERROR;
      break;
    }
  }
  if(
     (jointype & (JT_INNER|JT_OUTER))==(JT_INNER|JT_OUTER) ||
     (jointype & JT_ERROR)!=0
  ){
    static Token dummy = { 0, 0 };
    char *zSp1 = " ", *zSp2 = " ";
    if( pB==0 ){ pB = &dummy; zSp1 = 0; }
    if( pC==0 ){ pC = &dummy; zSp2 = 0; }
    sqliteSetNString(&pParse->zErrMsg, "unknown or unsupported join type: ", 0,
       pA->z, pA->n, zSp1, 1, pB->z, pB->n, zSp2, 1, pC->z, pC->n, 0);
    pParse->nErr++;
    jointype = JT_INNER;
  }else if( jointype & JT_RIGHT ){
    sqliteErrorMsg(pParse,
      "RIGHT and FULL OUTER JOINs are not currently supported");
    jointype = JT_INNER;
  }
  return jointype;
}
