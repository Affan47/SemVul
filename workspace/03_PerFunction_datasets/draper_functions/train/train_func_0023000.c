event_create(seq, size, etime, eline)
  seq_type seq;
  int size;
  time_type etime;
  int eline;
{
    event_type result = (event_type) chunk_alloc(seq, size);
    if (result) {
        result->ntime = etime;
        result->nline = eline;

        insert_event(seq, result);
        seq_duration(seq) = MAX(seq_duration(seq), etime);
    }
    return result;
}
