Evaluate(Function* f, double x) {
  Function::iterator iter =
      std::lower_bound(f->begin(), f->end(), x, FunctionDomainCmp());
  if (iter == f->begin()) {
    return (*f)[0].second;
  } else if (iter == f->end()) {
    ASSERT(f->size() >= 1);
    return (*f)[f->size() - 1].second;
  } else if (iter->first == x) {
    return iter->second;
  } else {
    double x1 = (iter - 1)->first;
    double y1 = (iter - 1)->second;
    double x2 = iter->first;
    double y2 = iter->second;
    return y1 + (y2 - y1) * (x - x1) / (x2 - x1);
  }
}
