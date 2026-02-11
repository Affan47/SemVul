cell_ewma_set_scale_factor(const or_options_t *options,
                           const networkstatus_t *consensus)
{
  int32_t halflife_ms;
  double halflife;
  const char *source;
  if (options && options->CircuitPriorityHalflife >= -EPSILON) {
    halflife = options->CircuitPriorityHalflife;
    source = "CircuitPriorityHalflife in configuration";
  } else if (consensus && (halflife_ms = networkstatus_get_param(
                 consensus, "CircuitPriorityHalflifeMsec",
                 -1, -1, INT32_MAX)) >= 0) {
    halflife = ((double)halflife_ms)/1000.0;
    source = "CircuitPriorityHalflifeMsec in consensus";
  } else {
    halflife = EWMA_DEFAULT_HALFLIFE;
    source = "Default value";
  }

  if (halflife <= EPSILON) {

    ewma_scale_factor = 0.1;
    ewma_enabled = 0;
    log_info(LD_OR,
             "Disabled cell_ewma algorithm because of value in %s",
             source);
  } else {

    halflife /= EWMA_TICK_LEN;

    ewma_scale_factor = exp( LOG_ONEHALF / halflife );
    ewma_enabled = 1;
    log_info(LD_OR,
             "Enabled cell_ewma algorithm because of value in %s; "
             "scale factor is %f per %d seconds",
             source, ewma_scale_factor, EWMA_TICK_LEN);
  }
}
