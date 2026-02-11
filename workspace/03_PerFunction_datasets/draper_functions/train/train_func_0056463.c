forward_signal(int sig)
{
   DENTER(TOP_LAYER, "forward_signal");
   if (child_pid > 0) {
      DPRINTF(("forwarding signal %d to child %d\n", sig, child_pid));
      kill(child_pid, sig);
   }
   DEXIT;
}
