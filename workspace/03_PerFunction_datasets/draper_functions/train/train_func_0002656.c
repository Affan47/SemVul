Abandon(void) {
    if(*this) {
      CloseStdout();
      CloseStderr();
      CloseStdin();
      abandoned_=true;
    }
  }
