getfree(Freelist *fl)
{
  int i;
  Freenode *t;

  if(fl->head == (Freenode *) NULL)
    {
      t =  (Freenode *) myalloc(sqrt_nsites * fl->nodesize);

      if(t == 0)
	return 0;

      currentMemoryBlock->next = new FreeNodeArrayList;
      currentMemoryBlock = currentMemoryBlock->next;
      currentMemoryBlock->memory = t;
      currentMemoryBlock->next = 0;

      for(i=0; i<sqrt_nsites; i+=1)
	makefree((Freenode *)((char *)t+i*fl->nodesize), fl);
    };
  t = fl->head;
  fl->head = (fl->head)->nextfree;
  return((char *)t);
}
