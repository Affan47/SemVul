GetDeltaMajor(int axis){
  if(axis>=0 && axis<=2)
    {
    return (this->DeltaMajor[axis]);
    }
  return 0;
}
