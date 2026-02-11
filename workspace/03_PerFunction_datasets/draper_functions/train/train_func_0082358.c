Wait(int timeout) {
    if (!started_) return false;
    if (!running_) return true;
    Glib::TimeVal till;
    till.assign_current_time();
    till += timeout;
    lock_.lock();
    while (running_) {
      Glib::TimeVal t;
      t.assign_current_time();
      t.subtract(till);
#ifdef HAVE_GLIBMM_CHILDWATCH
      if (!t.negative()) break;
      cond_.timed_wait(lock_, till);
#else
      int status;
      int r = ::waitpid(pid_->pid(), &status, WNOHANG);
      if (r == 0) {
        if (!t.negative()) break;
        lock_.unlock();
        sleep(1);
        lock_.lock();
        continue;
      }
      if (r == -1) {

        status = (-1)<<8;
      }

      lock_.unlock();
      child_handler(pid_->pid(), status);
      lock_.lock();
#endif
#ifdef DUAL_CHECK_LOST_CHILD
      if(running_) {
        if(!check_pid(pid_->pid(),exit_time_)) {
          lock_.unlock();
          child_handler(pid_->pid(), -1);
          lock_.lock();
        }
      }
#endif
    }
    lock_.unlock();
    return (!running_);
  }
