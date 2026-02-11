run()
  {
    if (0 == mutex->lock())
    {
      mtx_var = 2;
      OFStandard::sleep(1);
      if ((mtx_var == 2)&&(0 == mutex->unlock())) mtx_cond3 = 1;
    }
  }
}
