removeValNo(VNInfo *ValNo) {
  if (empty()) return;
  segments.erase(std::remove_if(begin(), end(), [ValNo](const Segment &S) {
    return S.valno == ValNo;
  }), end());

  markValNoForDeletion(ValNo);
}
