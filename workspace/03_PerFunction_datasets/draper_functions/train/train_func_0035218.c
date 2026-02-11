flush()
{
  if (!buf_.size()) {
    if (fd_ < 0)
      return;
    buf_.resize(bufSize);
    ptr_ = &buf_[0];
    end_ = ptr_ + buf_.size();
  }
  size_t n = ptr_ - &buf_[0];
  const char *s = buf_.data();
  while (n > 0) {
    int nw = ::write(fd_, s, n);
    if (nw < 0)
      break;
    n -= nw;
    s += nw;
  }
  ptr_ = &buf_[0];
}
