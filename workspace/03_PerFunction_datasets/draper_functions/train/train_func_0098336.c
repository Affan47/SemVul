advanceQ(t)
int t;
{
  if (Qhead == -1) {
    event_error("Internal error - empty queue");
  } else {
    Q[Qhead].delay = Q[Qhead].delay - t;
  };
}
