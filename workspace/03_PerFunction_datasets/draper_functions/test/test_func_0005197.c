Dequeue(Item *Owner)
{
   if (Owner->Status == pkgAcquire::Item::StatFetching)
      return _error->Error("Tried to dequeue a fetching object");

   bool Res = false;

   QItem **I = &Items;
   for (; *I != 0;)
   {
      if ((*I)->Owner == Owner)
      {
	 QItem *Jnk= *I;
	 *I = (*I)->Next;
	 Owner->QueueCounter--;
	 delete Jnk;
	 Res = true;
      }
      else
	 I = &(*I)->Next;
   }

   return Res;
}
