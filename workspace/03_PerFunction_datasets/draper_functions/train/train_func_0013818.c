Cycle()
{
   if (Items == 0 || Workers == 0)
      return true;

   if (PipeDepth < 0)
      return _error->Error("Pipedepth failure");


   QItem *I = Items;
   while (PipeDepth < (signed)MaxPipeDepth)
   {
      for (; I != 0; I = I->Next)
	 if (I->Owner->Status == pkgAcquire::Item::StatIdle)
	    break;


      if (I == 0)
	 return true;

      I->Worker = Workers;
      I->Owner->Status = pkgAcquire::Item::StatFetching;
      PipeDepth++;
      if (Workers->QueueItem(I) == false)
	 return false;
   }

   return true;
}
