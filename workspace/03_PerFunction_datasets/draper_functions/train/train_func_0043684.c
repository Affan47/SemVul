set(unsigned index,char aChar)
{
  if (index<length())
   {
     prepareToChange();
     data()[index]=aChar;
     changed();
     return MSError::MSSuccess;
   }
  return MSError::MSFailure;
}
