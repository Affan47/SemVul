uniformColumns(MSBoolean b_)
{
  if (b_!=uniformColumns())
   {
     if (b_==MSTrue) _stateFlag|=UniformColumns;
     else _stateFlag&=~UniformColumns;
     adjustSize();
   }
}
