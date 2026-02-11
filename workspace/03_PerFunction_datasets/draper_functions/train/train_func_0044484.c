removeAttribute (size_t index)
{
  size_t length = this->attrs_.size ();

  if (index >= length)
    return -1;

  this->attrs_[index] = this->attrs_[length - 1];
  this->attrs_.size (length - 1);

  return 0;
}
