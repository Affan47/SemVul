startRepeatTimer(TimerDirection dir_)
{
  if (_repeatTimer==0) _repeatTimer=new RepeatTimer(this,MSEntryFieldComboRepeatInterval,dir_);
  else
   {
     _repeatTimer->direction(dir_);
     _repeatTimer->reset();
   }
}
