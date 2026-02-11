getDefInit() {
  if (!TheInit)
    TheInit = new DefInit(this, new RecordRecTy(this));
  return TheInit;
}
