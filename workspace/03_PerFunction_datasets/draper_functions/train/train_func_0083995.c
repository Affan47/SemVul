style(unsigned long style_)
{

  unsigned long just=style_&(MSRight|MSLeft|MSTop|MSBottom|MSCenter);
  if (just>0) justification(just);
  _style=style_;
  return *this;
}
