make_pipe(void) {
  bool res = false;
  lock.lock();
  int filedes[2];
  kick_in=-1; kick_out=-1;
  if(pipe(filedes) == 0) {
    kick_in=filedes[1];
    kick_out=filedes[0];
    long arg;
    arg=fcntl(kick_in,F_GETFL);
    if(arg != -1) { arg|=O_NONBLOCK; fcntl(kick_in,F_SETFL,&arg); };
    arg=fcntl(kick_out,F_GETFL);
    if(arg != -1) { arg|=O_NONBLOCK; fcntl(kick_out,F_SETFL,&arg); };
    res = (kick_in != -1);
  };
  lock.unlock();
  return res;
}
