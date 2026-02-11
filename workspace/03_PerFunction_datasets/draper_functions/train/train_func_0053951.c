prepareToChange(void)
{
  if (_pData!=0)
   {
     if (_pData->refCount()>1) makeUniqueCopy();
   }
  else allocData(length());
}
