numberToChar(Number n, ISet<WideChar> &to,
				    Number &count)
     const
{
  if (type_ == number && n >= baseMin_ && n - baseMin_ < count_) {
    Number thisCount = count_ - (n - baseMin_);
    if (to.isEmpty() || thisCount < count)
      count = thisCount;
    to.add(descMin_ + (n - baseMin_));
  }
}
