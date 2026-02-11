pop()
{
   if (stack.size() < 1)
      return;

   AllocHeader* page = stack.back().page;
   currentPageOffset = stack.back().offset;

   while (inUseList != page)
   {

      inUseList->~AllocHeader();

      AllocHeader* nextInUse = inUseList->nextPage;
      if (inUseList->pageCount > 1)
         delete [] reinterpret_cast<char*>(inUseList);
      else
      {
         inUseList->nextPage = freeList;
         freeList = inUseList;
      }
      inUseList = nextInUse;
   }

   stack.pop_back();
}
