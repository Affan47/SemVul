undoNeighbourUpdates(neighbourUpdate *nu)
{
  simplex **thisPtr;
  simplex  *thisSimplex;


  while (!isEmpty(nu->ptrs))
  {
    thisPtr     = pop(nu->ptrs);
    thisSimplex = pop(nu->old);

    if (thisPtr)
      *thisPtr = thisSimplex;
  }
}
