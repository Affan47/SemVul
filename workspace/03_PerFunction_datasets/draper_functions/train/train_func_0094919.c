expression(FXint& flags){
  FXRexError err;
  FXint *at,*jp,flg;
  flags=FLG_WIDTH;
  at=pc;
  jp=NULL;
  err=alternative(flg);
  if(err!=REGERR_OK) return err;
  if(!(flg&FLG_WIDTH)) flags&=~FLG_WIDTH;
  while(*pat=='|'){
    pat++;
    insert(at,OP_BRANCH,pc-at+3);
    append(OP_JUMP,jp?jp-pc-1:0);
    jp=pc-1;
    at=pc;
    err=alternative(flg);
    if(err!=REGERR_OK) return err;
    if(!(flg&FLG_WIDTH)) flags&=~FLG_WIDTH;
    }
  patch(jp,pc);
  return REGERR_OK;
  }
