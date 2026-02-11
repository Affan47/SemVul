compexp(){
  FXExpressionError err=shiftexp();
  if(err!=EXPRERR_OK) return err;
  if(TK_LESS<=token && token<=TK_NOTEQUAL){
    FXuint t=token;
    gettok();
    err=shiftexp();
    if(err!=EXPRERR_OK) return err;
    if(t==TK_LESS) opcode(OP_LT);
    else if(t==TK_LESSEQ) opcode(OP_LE);
    else if(t==TK_GREATER) opcode(OP_GT);
    else if(t==TK_GREATEREQ) opcode(OP_GE);
    else if(t==TK_EQUAL) opcode(OP_EQ);
    else opcode(OP_NE);
    }
  return EXPRERR_OK;
  }
