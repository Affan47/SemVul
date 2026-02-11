allocHungoffUses(unsigned N) const {


  size_t size = N * sizeof(Use) + sizeof(Use::UserRef)
    + N * sizeof(BasicBlock*);
  Use *Begin = static_cast<Use*>(::operator new(size));
  Use *End = Begin + N;
  (void) new(End) Use::UserRef(const_cast<PHINode*>(this), 1);
  return Use::initTags(Begin, End);
}
