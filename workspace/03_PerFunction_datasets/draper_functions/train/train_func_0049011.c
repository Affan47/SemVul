Run() {
  const int kOneSecondInMicros = 1000000;


  server_->SetReuseAddress(true);


  bool bound = false;
  while (!bound && !terminate_) {
    bound = server_->Bind(port_);


    if (!bound) {
      PrintF("Failed to open socket on port %d, "
          "waiting %d ms before retrying\n", port_, kOneSecondInMicros / 1000);
      terminate_now_->Wait(kOneSecondInMicros);
    }
  }


  while (!terminate_) {
    bool ok = server_->Listen(1);
    listening_->Signal();
    if (ok) {

      Socket* client = server_->Accept();
      ok = client != NULL;
      if (ok) {

        CreateSession(client);
      }
    }
  }
}
