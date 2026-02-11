sigtermhandler(int num){
  static int tries = 0;
  if(tries++ <= 4){
    signal(num, sigtermhandler);
  } else {
    signal(num, SIG_DFL);
  }
  g_sigterm = TRUE;
  printfinfo("the termination signal %d catched", num);
}
