RemoveQuaternion(double t)
{
  if ( t < this->QuaternionList->front().Time ||
       t > this->QuaternionList->back().Time )
    {
    return;
    }

  QuaternionListIterator iter = this->QuaternionList->begin();
  for ( ; iter->Time != t && iter != this->QuaternionList->end(); ++iter )
    {
    }
  if ( iter != this->QuaternionList->end() )
    {
    this->QuaternionList->erase(iter);
    }

  this->Modified();
}
