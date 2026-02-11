energy(void) const
{
  unsigned long i;
  register StkFloat e = 0;
  if (inPoint_ >= outPoint_) {
    for (i=outPoint_; i<inPoint_; i++) {
      register StkFloat t = inputs_[i];
      e += t*t;
    }
  } else {
    for (i=outPoint_; i<inputs_.size(); i++) {
      register StkFloat t = inputs_[i];
      e += t*t;
    }
    for (i=0; i<inPoint_; i++) {
      register StkFloat t = inputs_[i];
      e += t*t;
    }
  }
  return e;
}
