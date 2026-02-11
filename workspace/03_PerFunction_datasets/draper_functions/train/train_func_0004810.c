rightJustify(unsigned newLength,char padCharacter)
{
  MSStringBuffer *result=this;

  if (newLength!=length())
   {
     unsigned prefix=(newLength>length())?newLength-length():0;
     unsigned fromReceiver=(length()<newLength)?length():newLength;

     result=newBuffer(0,prefix,
		      contents()+length()-fromReceiver,
		      fromReceiver,
		      0,0,
		      padCharacter);


     if (fromReceiver<length())
      {
	for (unsigned i=0;i<fromReceiver;i++)
	 {
	   if (charType(length()-fromReceiver+1+i)>MSStringEnum::DBCS1)
            {
	      result->contents()[i]=padCharacter;
	    }
	 }
      }
   }
  return result;
}
