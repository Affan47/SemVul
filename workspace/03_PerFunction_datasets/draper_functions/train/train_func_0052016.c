ArOptions_evaluate_values(ArOptions* ao)
{
  assert(ao != NULL);
  if (ao == NULL) {
    return;
  }
  if (ao->artries) {
    ao->tries = check_value_liberal(ao->artries, "Invalid ar-tries value");
  }
  if (ao->ardelay) {
    ao->delay = check_value(ao->ardelay, "Invalid ar-delay value");
  }
}
