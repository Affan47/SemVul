_ds_compute_weight_osb(const char *token) {


  int complexity = _ds_compute_complexity(token);


  if (complexity == 5) {
    return 3125;
  }

  if (complexity == 4) {
    return 256;
  }

  if (complexity == 3) {
    return 27;
  }

  if (complexity == 2) {
    return 4;
  }

  LOG(LOG_WARNING, "_ds_compute_weight_osb: no rule to compute OSB/OSBF/WINNOW weight for '%s'; complexity: %d", token, complexity);
  return 1;
}
