ScanText(
  const char *zText,
  GenState *pState
){
  int nextValid = 0;
  InStream sIn;
  Token sToken;
  Token sNext;


  sIn.z = zText;
  sIn.i = 0;
  sIn.nLine = 1;
  while( sIn.z[sIn.i]!=0 ){
    if( nextValid ){
      sToken = sNext;
      nextValid = 0;
    }else{
      GetNonspaceToken(&sIn,&sToken);
    }
    if( sToken.eType==TT_Id ){
      int needFullDecl;

      Decl *pDecl;


      pDecl = FindDecl(sToken.zText,sToken.nText);
      if( pDecl==0 ) continue;


      GetNonspaceToken(&sIn,&sNext);
      if( sNext.zText[0]=='*' ){
        needFullDecl = 0;
      }else{
        needFullDecl = 1;
        nextValid = sNext.eType==TT_Id;
      }


      DeclareObject(pDecl,pState,needFullDecl);
    }else if( sToken.eType==TT_Preprocessor ){
      sIn.i -= sToken.nText - 1;
    }
  }

}
