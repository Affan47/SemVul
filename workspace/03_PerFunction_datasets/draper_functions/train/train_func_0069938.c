out_stop ()
  {
    {
      Lock l (mutex_);
      stop_ = true;
      cond_.signal ();
    }

    tracker_mgr_.wait ();

    Element::out_stop ();
  }
