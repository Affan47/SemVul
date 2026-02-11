print_distance(const double distance, const int no_scale, const int with_tab, const int decis)
{
  double dist = distance;

  if (gtxt_flags.metric == 0) {
    dist = METERS_TO_FEET(dist);

    if ((dist < 5280) || no_scale) {
      gbfprintf(fout, "%.*f ft", decis, dist);
    } else {
      dist = METERS_TO_MILES(distance);
      if (dist < (double)100) {
        gbfprintf(fout, "%.1f mi", dist);
      } else {
        gbfprintf(fout, "%d mi", si_round(dist));
      }
    }
  } else {
    if ((dist < 1000) || no_scale) {
      gbfprintf(fout, "%.*f m", decis, dist);
    } else {
      dist = dist / (double)1000.0;
      if (dist < (double)100) {
        gbfprintf(fout, "%.1f km", dist);
      } else {
        gbfprintf(fout, "%d km", si_round(dist));
      }
    }
  }
  if (with_tab) {
    gbfprintf(fout, "\t");
  }
}
