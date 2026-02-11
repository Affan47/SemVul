assign (GPEnabled *nptr)
{
  if (nptr && atomicIncrement(&nptr->count) <= 0)
    nptr = 0;
  GPEnabled *optr = (GPEnabled*)atomicExchangePointer((void**)&ptr, (void*)nptr);
  if (optr)
    optr->unref();
  return *this;
}
