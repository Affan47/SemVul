dispatch_pending(Connection::PrivatePList &pending_queue)
{


  _mutex_p_copy.lock();
  while (pending_queue.size() > 0)
  {
    Connection::PrivatePList::iterator i, j;

    i = pending_queue.begin();

    while (i != pending_queue.end())
    {
      j = i;

      ++j;

      if ((*i)->do_dispatch())
        pending_queue.erase(i);
      else
        debug_log("dispatch_pending_private: do_dispatch error");

      i = j;
    }
  }
  _mutex_p_copy.unlock();
}
