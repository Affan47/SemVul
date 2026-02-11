removeModifiedCB(ArFunctor *functor)
{
  if (functor == NULL) {
    return false;
  }

  lock();


  myModifiedCBList.remove(functor);
  unlock();

  return true;

}
