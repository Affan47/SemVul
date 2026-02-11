Shift(size_t size) {
  if (size > Length())
    return false;

  end_ = Length() - size;
  memmove(bytes_, bytes_ + start_ + size, end_);
  start_ = 0;
  return true;
}

}
