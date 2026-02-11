hasLaser(ArLaser *device) const
{
  for(std::map<int, ArLaser*>::const_iterator i = myLaserMap.begin();
        i != myLaserMap.end(); ++i)
  {
     if( (*i).second == device ) return true;
  }
  return false;
}
