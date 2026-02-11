value(int value_)
{
  if (value_!=value())
   {
     valueChange(value_);
     _changeType=ValueChange;
     notify(value());
   }
}
