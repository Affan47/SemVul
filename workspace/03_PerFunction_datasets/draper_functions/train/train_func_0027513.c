Body(PayloadRawInterface& body,bool ownership) {
  if(rbody_ && body_own_) delete rbody_;
  if(sbody_ && body_own_) delete sbody_;
  sbody_ = NULL;
  rbody_=&body; body_own_=ownership;
}
