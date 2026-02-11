med(void) const {

    if (fst() == NULL)
      return (dom.min()+dom.max())/2 - ((dom.min()+dom.max())%2 < 0 ? 1 : 0);
    unsigned int i = size() / 2;
    if (size() % 2 == 0)
      i--;
    const RangeList* p = NULL;
    const RangeList* c = fst();
    while (i >= c->width()) {
      i -= c->width();
      const RangeList* n=c->next(p); p=c; c=n;
    }
    return c->min() + static_cast<int>(i);
  }
