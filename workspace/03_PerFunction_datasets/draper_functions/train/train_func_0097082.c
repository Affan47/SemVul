parse_features (const char *name G_GNUC_UNUSED,
	        const char *arg,
	        gpointer    data,
	        GError    **error G_GNUC_UNUSED)
{
  shape_options_t *shape_opts = (shape_options_t *) data;
  char *s = (char *) arg;
  char *p;

  shape_opts->num_features = 0;
  g_free (shape_opts->features);
  shape_opts->features = NULL;

  if (!*s)
    return true;


  p = s;
  do {
    shape_opts->num_features++;
    p = strchr (p, ',');
    if (p)
      p++;
  } while (p);

  shape_opts->features = (hb_feature_t *) calloc (shape_opts->num_features, sizeof (*shape_opts->features));


  p = s;
  shape_opts->num_features = 0;
  while (p && *p) {
    char *end = strchr (p, ',');
    if (hb_feature_from_string (p, end ? end - p : -1, &shape_opts->features[shape_opts->num_features]))
      shape_opts->num_features++;
    p = end ? end + 1 : NULL;
  }

  return true;
}
