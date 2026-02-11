enablePostRAScheduler() const {


  if (getSchedModel().isOutOfOrder() && isSwift())
    return false;
  return (!isThumb() || hasThumb2());
}
