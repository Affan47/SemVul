lower_omp (gimple_seq body, omp_context *ctx)
{
  location_t saved_location = input_location;
  gimple_stmt_iterator gsi = gsi_start (body);
  for (gsi = gsi_start (body); !gsi_end_p (gsi); gsi_next (&gsi))
    lower_omp_1 (&gsi, ctx);
  input_location = saved_location;
}
