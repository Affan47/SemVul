hasPassword(){
  FXMutexLock lock(mutex_data);
  return !password.empty();
  }
