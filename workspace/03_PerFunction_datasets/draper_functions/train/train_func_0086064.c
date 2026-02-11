FindItem(string URI,pkgAcquire::Worker *Owner)
{
   for (QItem *I = Items; I != 0; I = I->Next)
      if (I->URI == URI && I->Worker == Owner)
	 return I;
   return 0;
}
