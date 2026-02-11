Kill(int timeout) {
#ifndef HAVE_GLIBMM_CHILDWATCH
    Wait(0);
#endif
    if (!running_) return;
    if (timeout > 0) {

      ::kill(pid_->pid(), SIGTERM);
      Wait(timeout);
    }
    if (!running_) return;

    ::kill(pid_->pid(), SIGKILL);
  }
