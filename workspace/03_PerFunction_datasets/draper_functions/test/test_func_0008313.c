traverse(TIntermTraverser* it)
{
   bool visit = true;

   if (it->preVisit && it->visitBranch)
      visit = it->visitBranch(true, this, it);

   if (visit && expression)
   {
      ++it->depth;
      expression->traverse(it);
      --it->depth;
   }

   if (visit && it->postVisit && it->visitBranch)
      it->visitBranch(false, this, it);
}
