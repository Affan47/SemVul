ep_reset (struct event_set *es)
{
  const struct ep_set *eps = (struct ep_set *) es;
  ASSERT (eps->fast);
}
