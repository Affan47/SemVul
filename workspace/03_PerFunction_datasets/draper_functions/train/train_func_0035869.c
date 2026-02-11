removeStaleShmObjects()
{
  dmtcp::vector<int> staleShmids;
  for (ShmIterator i = _shm.begin(); i != _shm.end(); ++i) {
    ShmSegment& shmObj = i->second;
    if (shmObj.isStale()) {
      staleShmids.push_back(i->first);
    }
  }
  for (size_t j = 0; j < staleShmids.size(); ++j) {
    _shm.erase(staleShmids[j]);
  }
}
