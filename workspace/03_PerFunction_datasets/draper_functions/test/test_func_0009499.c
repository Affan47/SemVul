AllocateSegment(int length) {
  LOG(DEBUG) << "allocating segment of size " << length;
  vector<Address*>* ts = new vector<Address*>(length);

  for (int l = 0; l < length; l++) {
    (*ts)[l] = new Address(this);
  }


  for (int l = 0; l < length-1; l++) {
    (*ts)[l]->set_next((*ts)[l+1]);
  }

  segments_.push_back(ts);
  return ts;
}
