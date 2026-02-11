minSubtreeTip (nodeptr  p0)
  {
    nodeptr  minTip, p, testTip;

    if (p0->tip) return p0;

    p = p0->next;
    minTip = minSubtreeTip(p->back);
    while ((p = p->next) != p0) {
      testTip = minSubtreeTip(p->back);
      if (cmpTipVal(tipValPtr(testTip), tipValPtr(minTip)) < 0)
        minTip = testTip;
      }
    return minTip;
  }
