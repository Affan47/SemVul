getArgsWithFunctor(bool *ok) const
{
  if (ok != NULL) {
    *ok = (myType == FUNCTOR);
  }
  if (myType == FUNCTOR) {
    if (myData.myFunctorData.myGetFunctor != NULL)
      return myData.myFunctorData.myGetFunctor->invokeR();
  }
  return NULL;
}
