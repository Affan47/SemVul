placestartrep(j)

int j;
{
  if (quiet == -1) event_warning("Assuming repeat");
  switch(feature[j]) {
  case DOUBLE_BAR:
    feature[j] = BAR_REP;
    break;
  case SINGLE_BAR:
    feature[j] = BAR_REP;
    break;
  case REP_BAR:
    if (quiet == -1) event_warning("replacing |: with double repeat (::)");
    feature[j] = DOUBLE_REP;
    break;
  case BAR_REP:
    if (quiet == -1) event_error("Too many end repeats");
    break;
  case DOUBLE_REP:
    if (quiet == -1) event_error("Too many end repeats");
    break;
  default:
    event_error("Internal error - please report");
    break;
  };
}
