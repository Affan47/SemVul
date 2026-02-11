radius_init(const char *args)
{
  char *fm;

  pos_dist = 0;

  if (distopt) {
    pos_dist = strtod(distopt, &fm);

    if ((*fm == 'k') || (*fm == 'K')) {

      pos_dist *= .6214;
    }
  }

  if (maxctarg) {
    maxct = atoi(maxctarg);
  } else {
    maxct = 0;
  }

  home_pos = (waypoint *) xcalloc(sizeof(*home_pos), 1);

  if (latopt) {
    home_pos->latitude = atof(latopt);
  }
  if (lonopt) {
    home_pos->longitude = atof(lonopt);
  }
}
