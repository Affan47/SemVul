SST_AccumulateSample(SST_Stats inst, struct timeval *sample_time,
                     double offset,
                     double peer_delay, double peer_dispersion,
                     double root_delay, double root_dispersion,
                     int stratum)
{
  int n, m;


  if (inst->n_samples > 0 &&
      (inst->n_samples == MAX_SAMPLES || inst->n_samples == max_samples)) {
    prune_register(inst, 1);
  }


  if (inst->n_samples &&
      UTI_CompareTimevals(&inst->sample_times[inst->last_sample], sample_time) >= 0) {
    LOG(LOGS_WARN, LOGF_SourceStats, "Out of order sample detected, discarding history for %s",
        inst->ip_addr ? UTI_IPToString(inst->ip_addr) : UTI_RefidToString(inst->refid));
    prune_register(inst, inst->n_samples);
  }

  n = inst->last_sample = (inst->last_sample + 1) %
    (MAX_SAMPLES * REGRESS_RUNS_RATIO);
  m = n % MAX_SAMPLES;

  inst->sample_times[n] = *sample_time;
  inst->offsets[n] = offset;
  inst->orig_offsets[m] = offset;
  inst->peer_delays[m] = peer_delay;
  inst->peer_dispersions[m] = peer_dispersion;
  inst->root_delays[m] = root_delay;
  inst->root_dispersions[m] = root_dispersion;
  inst->strata[m] = stratum;

  if (!inst->n_samples || inst->peer_delays[m] < inst->peer_delays[inst->min_delay_sample])
    inst->min_delay_sample = m;

  ++inst->n_samples;
}
