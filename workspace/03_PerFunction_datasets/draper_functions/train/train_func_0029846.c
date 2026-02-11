mailstream_setup_idle(mailstream * s)
{
  if (s->idling) {
    return -1;
  }

  if (s->low->driver == mailstream_cfstream_driver) {
    mailstream_cfstream_setup_idle(s);
  }
  else {
    s->idle = mailstream_cancel_new();
    if (s->idle == NULL)
      return -1;
  }

  s->idling = 1;

  return 0;
}
