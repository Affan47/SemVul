Remove(Worker *Work)
{
   if (Running == true)
      abort();

   Worker **I = &Workers;
   for (; *I != 0;)
   {
      if (*I == Work)
	 *I = (*I)->NextAcquire;
      else
	 I = &(*I)->NextAcquire;
   }
}
