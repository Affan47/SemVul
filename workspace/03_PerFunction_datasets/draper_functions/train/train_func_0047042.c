ParseLineDup(Parse parse, ParsedLine line)
#else
ParsedLine ParseLineDup(parse, line)
     Parse parse;
     ParsedLine line;
#endif
{
  int i;
  ParsedLine nline;


  if( !parse ) return NULL;


  if( !(nline = (ParsedLine)xcalloc(1, sizeof(ParsedLineRec))) ) return NULL;
  memcpy(nline, line, sizeof(ParsedLineRec));
  nline->tokens = (ParsedToken)xcalloc(line->maxtoken, sizeof(ParsedTokenRec));
  memcpy(nline->tokens, line->tokens, line->maxtoken*sizeof(ParsedTokenRec));
  for(i=0; i<nline->ntoken; i++){
    nline->tokens[i].sval = xstrdup(line->tokens[i].sval);
  }
  nline->types = (char *)xcalloc((line->maxtoken+1), sizeof(char));
  memcpy(nline->types, line->types, line->maxtoken+1);
  return nline;
}
