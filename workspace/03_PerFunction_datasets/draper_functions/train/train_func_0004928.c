clear_connection_data(struct connection_data *conn)
{
  int pos;

  conn->queue_start = 0;
  conn->queue_end = 0;
  for (pos = BOARDMIN; pos < BOARDMAX; pos++) {
    conn->distances[pos] = HUGE_CONNECTION_DISTANCE;
    conn->deltas[pos] = FP(0.0);
    conn->coming_from[pos] = NO_MOVE;
    conn->vulnerable1[pos] = NO_MOVE;
    conn->vulnerable2[pos] = NO_MOVE;
  }

  conn->heap_data_size = 0;
  conn->heap_size = 0;
}
