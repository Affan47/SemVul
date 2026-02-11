MaybeRecomputeCheckSum() const {
  {
    ReaderMutexLock check_sum_lock(&check_sum_mutex_);
    if (check_sum_finalized_)
      return;
  }


  MutexLock check_sum_lock(&check_sum_mutex_);
  if (check_sum_finalized_)
    return;


  CheckSummer check_sum;
  for (int64 i = 0; i < symbols_.size(); ++i) {
    const string& sym = symbols_.GetSymbol(i);
    check_sum.Update(sym.data(), sym.size());
    check_sum.Update("", 1);
  }
  check_sum_string_ = check_sum.Digest();


  CheckSummer labeled_check_sum;
  for (int64 i = 0; i < dense_key_limit_; i++) {
    ostringstream line;
    line << symbols_.GetSymbol(i) << '\t' << i;
    labeled_check_sum.Update(line.str().data(), line.str().size());
  }
  for (map<int64, int64>::const_iterator i
         = key_map_.begin(); i != key_map_.end(); ++i) {


    if (i->first < dense_key_limit_) continue;

    ostringstream line;
    line << symbols_.GetSymbol(i->second) << '\t' << i->first;
    labeled_check_sum.Update(line.str().data(), line.str().size());
  }
  labeled_check_sum_string_ = labeled_check_sum.Digest();

  check_sum_finalized_ = true;
}
