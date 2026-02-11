operator-() const
{
  if (digits_ == 0) return *this;

  IDL_Fixed r(*this);
  r.negative_ = !r.negative_;
  return r;
}
