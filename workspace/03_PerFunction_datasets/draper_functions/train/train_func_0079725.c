callAFunc(A fun_,A cd_)
{
  typedef void *XClientArg;
  typedef void *XCallArg;
  extern void ACallback(XCallArg,XClientArg);
  AClientData *ac=new AClientData(model()->aplusVar(),(A)fun_,(A)cd_);
  ACallback(this,ac);
  delete ac;
}
