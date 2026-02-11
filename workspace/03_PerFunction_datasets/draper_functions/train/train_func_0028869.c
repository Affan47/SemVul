GenerateObjectEquals(ZoneList<Expression*>* args) {
  ASSERT(args->length() == 2);


  Load(args->at(0));
  Load(args->at(1));
  Result right = frame_->Pop();
  Result left = frame_->Pop();
  right.ToRegister();
  left.ToRegister();
  __ cmpq(right.reg(), left.reg());
  right.Unuse();
  left.Unuse();
  destination()->Split(equal);
}
