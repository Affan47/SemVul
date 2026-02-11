gc(ExprValue* ev) {
  if(!d_disableGC) {
    d_exprSet.erase(ev);
    if (d_inGC) d_pending.push_back(ev);
    else if (d_postponeGC) d_postponed.push_back(ev);
    else {
      IF_DEBUG(FatalAssert(d_pending.size() == 0, "Expected size 1");)
      d_inGC = true;
      size_t tp = ev->getMMIndex();
      delete ev;
      d_mm[tp]->deleteData(ev);
      while (d_pending.size() > 0) {
        ev = d_pending.front();
        d_pending.pop_front();
        tp = ev->getMMIndex();
        delete ev;
        d_mm[tp]->deleteData(ev);
      }
      d_inGC = false;
    }
  }
}
