collapse (Queue& q)
  {


    u64 sn (q.sn () + 1);

    for (;; ++sn)
    {
      Queue::ENTRY* e = 0;

      if (q.find (sn, e) == -1 || e->int_id_.lost ()) break;

      Message_ptr m (e->int_id_.msg ());
      q.unbind (sn);

      in_->recv (m);
    }

    q.sn (sn - 1);
  }
