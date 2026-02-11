live_reconfigure(Vector<String> &conf, ErrorHandler *errh)
{
  if (can_live_reconfigure())
    return configure(conf, errh);
  else
    return errh->error("cannot reconfigure %{element} live", this);
}
