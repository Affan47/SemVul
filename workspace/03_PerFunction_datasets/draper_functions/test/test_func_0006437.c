stop(void) {


  if (!socket_error_notify.in_main_thread()) {
    write_error("Call to SocketServer::stop() in other than the main thread\n");
    return;
  }

  if (server_running) {
    thread->cancel();
    cleanup();
  }
}
