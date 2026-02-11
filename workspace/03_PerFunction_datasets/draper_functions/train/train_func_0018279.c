run()
  {
    if (OFMutex::busy == mutex->trylock()) mtx_cond1=1;
    if (0 == mutex->lock())
    {
      mtx_var = 1;
      OFStandard::sleep(1);
      if ((mtx_var == 1)&&(0 == mutex->unlock())) mtx_cond2 = 1;
    }
  }
}
