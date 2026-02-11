style(unsigned long style_)
{
  unsigned long temp=style_&(MSLeft|MSRight|MSTop|MSBottom|MSCenter);
  if (temp>0) justification(temp);
  _style=style_^temp;
  return *this;
}
