skip_bytes (size_t len)
{
  if (this->rd_ptr () + len <= this->wr_ptr ())
    {
      this->rd_ptr (len);
      return true;
    }
  this->good_bit_ = false;
  return false;
}
