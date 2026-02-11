getSRMFileInfo(SRMFileInfo& srm_file_info) {

  lock.lock();
  for (std::list<SRMFileInfo>::const_iterator i = srm_info.begin(); i != srm_info.end(); ++i) {
    if (i->host == srm_file_info.host && i->version == srm_file_info.version) {
      srm_file_info.port = i->port;
      lock.unlock();
      return true;
    }
  }
  lock.unlock();
  return false;
}
