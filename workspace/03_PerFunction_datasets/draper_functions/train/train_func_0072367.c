skip_hollerith(srcPosn pos)
{
  int len=0;
  int c;
  while(isdigit(c=pos.Line->line[pos.idx])) {
    len = len*10 + BCD(c);
    stepPosn(&pos);
    SKIP_SPACE;
  }
#ifdef DEBUG_IS_KEYWORD
if(debug_lexer && getenv("VERBOSE"))
  (void)fprintf(list_fd,"\nskip_hollerith: %d then %c:",
len,pos.Line->line[pos.idx]);
#endif
  if(makeupper(pos.Line->line[pos.idx]) != 'H')
    return pos;

  stepPosn(&pos);

  while(pos.Line->line[pos.idx] != '\0' && len > 0){

#ifdef DEBUG_IS_KEYWORD
if(debug_lexer && getenv("VERBOSE"))
  (void)fprintf(list_fd,"%c",pos.Line->line[pos.idx]);
#endif
    --len; stepPosn(&pos);
  }
#ifdef DEBUG_IS_KEYWORD
if(debug_lexer && getenv("VERBOSE"))
  (void)fprintf(list_fd," to %c",pos.Line->line[pos.idx]);
#endif
  return pos;
}
