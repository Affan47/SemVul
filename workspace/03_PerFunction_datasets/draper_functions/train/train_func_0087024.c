parseAssembly(machine_6502 *machine, BOOL *codeOk, const char *code){
  char *s;
  char *cmd = ecalloc(MAX_CMD_LEN, sizeof(char));
  char *label = ecalloc(MAX_LABEL_LEN, sizeof(char));
  char *start;
  unsigned int lc = 1;
  Param *param;
  BOOL decl;
  AsmLine *listp = NULL;

  *codeOk = TRUE;
  param = newParam();
  s = estrdup(code);
  start = s;
  stoupper(&s);

  while(*s != '\0' && *codeOk){
    initParam(param);
    nullify(cmd, MAX_CMD_LEN);
    nullify(label, MAX_LABEL_LEN);
    decl = FALSE;
    skipSpace(&s);
    comment(&s);
    if (*s == '\n'){
      lc++;
      s++;
      continue;
    }
    else if (*s == '\0')
      continue;
    else if (hasChar(s,':')){
      decl = TRUE;
      if(! declareLabel(&s,&label)){
	*codeOk = FALSE;
	break;
      }
      skipSpace(&s);
    }
    if(!command(machine, &s, &cmd)){
      *codeOk = FALSE;
      break;
    }
    skipSpace(&s);
    comment(&s);
    if(!parameter(cmd, &s, param)){
      *codeOk = FALSE;
      break;
    }
    skipSpace(&s);
    comment(&s);
    if (*s == '\n' || *s == '\0'){
      AsmLine *asmm;
      asmm = newAsmLine(cmd,label,decl,param,lc);
      listp = addend(listp,asmm);
    }
    else {
      *codeOk = FALSE;
      break;
    }
  }
  if (! *codeOk)
    fprintf(stderr,"Syntax error at line %u\n", lc);
  free(start);
  free(cmd);
  free(label);
  freeParam(param);
  return listp;
}
