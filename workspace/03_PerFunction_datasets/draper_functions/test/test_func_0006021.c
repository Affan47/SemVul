isRepLock() const
  {
    if (m->status->entry && (m->status->entry->lock_token != 0))
      return false;
    else if (m->status->repos_lock && (m->status->repos_lock->token != 0))
      return true;
    else
      return false;
  }
