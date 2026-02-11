gtp_estimate_score(char *s)
{
  float score;
  float upper_bound, lower_bound;
  UNUSED(s);

  score = gnugo_estimate_score(&upper_bound, &lower_bound);
  gtp_start_response(GTP_SUCCESS);

  if (score >= 0.0)
    gtp_printf("W+%3.1f (upper bound: %3.1f, lower: %3.1f)",
	       score, upper_bound, lower_bound);
  else if (score < 0.0)
    gtp_printf("B+%3.1f (upper bound: %3.1f, lower: %3.1f)",
	       -score, upper_bound, lower_bound);
  return gtp_finish_response();
}
