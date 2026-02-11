RemoveData(void) {
    Glib::Thread* self = Glib::Thread::self();
    lock_.lock();
    datas_iterator d = datas_.find(self);
    if(d != datas_.end()) {
      ThreadData* data = d->second;
      datas_.erase(d);
      lock_.unlock();
      data->Release();

      return;
    }
    lock_.unlock();
  }
