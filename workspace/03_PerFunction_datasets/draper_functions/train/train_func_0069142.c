is_written(int handle) {
    lock.lock();
    if (bufs == NULL) {
      lock.unlock();
      return false;
    }
    if (handle >= bufs_n) {
      lock.unlock();
      return false;
    }
    if (!bufs[handle].taken_for_write) {
      lock.unlock();
      return false;
    }

    if (!speed.transfer(bufs[handle].used))
      if ((!(error_read_flag || error_write_flag)) &&
          (!(eof_read_flag && eof_write_flag))) {
        error_transfer_flag = true;
    }
    bufs[handle].taken_for_write = false;
    bufs[handle].used = 0;
    bufs[handle].offset = 0;
    cond.broadcast();
    lock.unlock();
    return true;
  }
