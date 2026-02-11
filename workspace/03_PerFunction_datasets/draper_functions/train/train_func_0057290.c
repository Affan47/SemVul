sighup_handler(int) {
    int old_errno = errno;
    if(main_daemon) main_daemon->logreopen();
    for (std::list<Arc::LogFile*>::iterator dest = sighup_dests.begin();
         dest != sighup_dests.end(); ++dest) {
      if(*dest) {
        (*dest)->setReopen(true);
        (*dest)->setReopen(false);
      }
    }
    errno = old_errno;
}
