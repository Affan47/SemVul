fileExists(const char* name) const {
    SCOPED_LOCK_MUTEX(files_mutex);
    return files->exists((char*)name);
  }
