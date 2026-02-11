read_pipe_cb(bool&) {
  void* instance_p;
  int remaining = sizeof(void*);
  ssize_t result;
  char* temp_p = reinterpret_cast<char*>(&instance_p);
  do {
    result = Notifier::pipe.read(temp_p, remaining);
    if (result > 0) {
      temp_p += result;
      remaining -= result;
    }
  } while (remaining
	   && result
	   && result != -1);

  if (result > 0) {
    if (instance_p == 0) g_critical("Null pointer passed in Notifier::read_pipe_cb()\n");
    else {
      Notifier* notifier_p = static_cast<Notifier*>(instance_p);

      {
	Thread::Mutex::Lock lock(*set_mutex_p);
	if (object_set.find(notifier_p) == object_set.end()) return;
      }


      notifier_p->emitter();
    }
  }

  else {


    g_critical("IO error in Notifier::read_pipe_cb()\n");
  }
}

}
