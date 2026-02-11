powexp(){
  FXExpressionError err=primary();
  if(err!=EXPRERR_OK) return err;
  if(token==TK_POWER){
    gettok();
    err=powexp();
    if(err!=EXPRERR_OK) return err;
    opcode(OP_POW);
    }
  return EXPRERR_OK;
  }
