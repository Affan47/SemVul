setClientThreadCallTimeout(CORBA::ULong v)
{
  omniCurrent* current = omniCurrent::get();
  if (!current)
    OMNIORB_THROW(INITIALIZE, INITIALIZE_NotOmniThread, CORBA::COMPLETED_NO);

  current->setTimeout(v / 1000, (v % 1000) * 1000000);
}
