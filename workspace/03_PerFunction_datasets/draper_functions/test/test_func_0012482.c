mailstream_interrupt_idle(mailstream * s)
{
  if (!s->idling) {
    return;
  }

  if (s->low->driver == mailstream_cfstream_driver) {
    mailstream_cfstream_interrupt_idle(s);
  }
  else {
    mailstream_cancel_notify(s->idle);
  }
}
