IsUnresolvedIP() const {
  return IsAny() && !literal_ && !hostname_.empty();
}
