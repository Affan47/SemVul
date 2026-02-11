operator=(const vnl_bignum& rhs)
{
  if (this != &rhs) {
    delete[] this->data;
    this->count = rhs.count;
    this->data = rhs.data ? new Data[rhs.count] : 0;
    for (Counter i = 0; i < rhs.count; ++i)
      this->data[i] = rhs.data[i];
    this->sign = rhs.sign;
  }
  return *this;
}
