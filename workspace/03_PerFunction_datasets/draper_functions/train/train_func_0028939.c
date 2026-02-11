emit() {


  if (in_main_thread()) {
    emitter();
  }

  else {

    Thread::Mutex::Lock lock(*write_mutex_p);
    void* instance_p = this;
    pipe.write(reinterpret_cast<char*>(&instance_p), sizeof(void*));
  }
}
