possibleTransitions(const AndState &andState,
				      unsigned minAndDepth,
				      Vector<const ElementType *> &v) const
{
  Vector<LeafContentToken *>::const_iterator p = follow_.begin();
  if (!andInfo_) {
    for (size_t n = follow_.size(); n > 0; n--, p++)
      v.push_back((*p)->elementType());
  }
  else {
    Vector<Transition>::const_iterator q = andInfo_->follow.begin();
    for (size_t n = follow_.size(); n > 0; n--, p++, q++)
      if ((q->requireClear == unsigned(Transition::invalidIndex)
	   || andState.isClear(q->requireClear))
	&& q->andDepth >= minAndDepth)
	v.push_back((*p)->elementType());
  }
}
