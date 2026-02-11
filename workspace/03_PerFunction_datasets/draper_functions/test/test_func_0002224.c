adjustSize(void)
{
  if (firstMap()==MSTrue&&frozen()==MSFalse)
   {
     if (lockPositions()==MSFalse) recomputeVectors();
     _vectorState=Minimum;
     if (lockSize()==MSFalse) resize(idealWidth(),idealHeight());
     else
      {
	placement();
        configure();
      }
   }
}
