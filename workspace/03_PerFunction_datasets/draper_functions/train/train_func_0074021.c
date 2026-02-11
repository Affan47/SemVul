run()
{
  int idle_time_btw_chkpt;
  char *itbc = getenv("OMNINAMES_ITBC");
  if (itbc == NULL || sscanf(itbc,"%d",&idle_time_btw_chkpt) != 1)
    idle_time_btw_chkpt = DEFAULT_IDLE_TIME_BTW_CHKPT;

  {
    omni_mutex_lock sync(mu_);


    running_ = 1;
    cond_.signal();

    do {
      log_->checkpoint();
      unsigned long s, n;
      omni_thread::get_time(&s, &n, idle_time_btw_chkpt);
      cond_.timedwait(s,n);
    } while (!stop_);
  }
  {
    time_t t = time(NULL);
    char *p = ctime(&t);
    cerr << endl << p << endl << "omniNames shutting down." << endl;
  }
}
