job_input_status_read_file(const JobId &id,const GMConfig &config,std::list<std::string>& files) {
  std::string fname = config.ControlDir() + "/job." + id + sfx_inputstatus;
  Arc::FileLock lock(fname);
  for (int i = 10; !lock.acquire() && i >= 0; --i) {
    if (i == 0) return false;
    sleep(1);
  }
  bool r = Arc::FileRead(fname, files);
  lock.release();
  return r;
}
