analyze(SAMPLE_BUFFER* sbuf)
{
  parameter_t etime = begtime_rep + durtime_rep;
  parameter_t curtime = static_cast<parameter_t>(position_in_samples_rep) / samples_per_second();

  if (curtime >= begtime_rep) {


    if (begtime_rep == etime)
      open_gate();
    else if (curtime < etime)
      open_gate();
    else
      close_gate();
  }
  else
    close_gate();

  position_in_samples_rep += sbuf->length_in_samples();
}
