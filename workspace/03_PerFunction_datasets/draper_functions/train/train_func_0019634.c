features (fsp_link *link, const char *string)
{
  if (link->features) {
    if (strcmp(link->features, string)) {
      link_error(LOG_WARNING, "features inconsistent between segments");
    }
  } else {
    link->features = strdup(string);
  }
}
