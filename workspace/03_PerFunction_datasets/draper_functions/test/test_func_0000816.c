connection_bucket_refill_helper(int *bucket, int rate, int burst,
                                int milliseconds_elapsed,
                                const char *name)
{
  int starting_bucket = *bucket;
  if (starting_bucket < burst && milliseconds_elapsed > 0) {
    int64_t incr = (((int64_t)rate) * milliseconds_elapsed) / 1000;
    if ((burst - starting_bucket) < incr) {
      *bucket = burst;

    } else {
      *bucket += (int)incr;
      if (*bucket > burst || *bucket < starting_bucket) {


        *bucket = burst;
      }
    }
    log(LOG_DEBUG, LD_NET,"%s now %d.", name, *bucket);
  }
}
