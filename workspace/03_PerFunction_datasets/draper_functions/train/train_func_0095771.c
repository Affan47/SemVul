AddConsumer(std::string& id,const std::string& client) {
  lock_.lock();
  if(id.empty()) {
    for(int tries = 0;tries<1000;++tries) {
      GUID(id);
      ConsumerIterator i = consumers_.find(id);
      if(i == consumers_.end()) break;
      id.resize(0);
    };
    if(id.empty()) {
      failure_ = "Failed to generate unique identifier";
      lock_.unlock();
      return NULL;
    };
  } else {
    ConsumerIterator i = consumers_.find(id);
    if(i != consumers_.end()) {
      failure_ = "Requested identifier already in use";
      lock_.unlock();
      return NULL;
    };
  };
  Consumer c;
  c.deleg=new DelegationConsumerSOAP();
  c.client_id=client;
  c.previous=consumers_.end();
  c.next=consumers_first_;
  ConsumerIterator i = consumers_.insert(consumers_.begin(),make_pair(id,c));
  if(consumers_first_ != consumers_.end()) consumers_first_->second.previous=i;
  consumers_first_=i;
  if(consumers_last_ == consumers_.end()) consumers_last_=i;
  i->second.acquired = 1;
  DelegationConsumerSOAP* cs = i->second.deleg;
  lock_.unlock();
  return cs;
}
