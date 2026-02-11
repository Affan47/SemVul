func(void* arg) {
    if(!arg) return;


    Arc::Logger::getRootLogger().setThreadContext();
    Arc::Logger::getRootLogger().removeDestinations();


    DataDeliveryCommHandler& it = *(DataDeliveryCommHandler*)arg;
    for(;;) {
      {
        Glib::Mutex::Lock lock(it.lock_);
        for(std::list<DataDeliveryComm*>::iterator i = it.items_.begin();
                  i != it.items_.end();++i) {
          DataDeliveryComm* comm = *i;
          if(comm)
            comm->PullStatus();
        }
      }
      Glib::usleep(500000);
    }
  }

}
