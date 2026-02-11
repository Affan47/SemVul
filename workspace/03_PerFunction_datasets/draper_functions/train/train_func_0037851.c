write_stdout_from_thread(const char* message) {


  if (stdout_notify.in_main_thread()) {
    write_error("Call to SocketServer::write_stdout_from_thread() from "
		"the main GUI thread\n");
    return;
  }

  Thread::Mutex::Lock lock(stdout_mutex);


  while (!stdout_text.empty()) stdout_cond.wait(stdout_mutex);

  stdout_text = message;
  stdout_notify();
}
