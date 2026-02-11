OnPosixSignalReceived(int signum) {
    if (signum >= ARRAY_SIZE(received_signal_)) {

      return;
    }

    received_signal_[signum] = true;

    const uint8 b[1] = { 0 };
    if (-1 == write(afd_[1], b, sizeof(b))) {


      return;
    }
  }
