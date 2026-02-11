ppdb_read_wpt(route_head *head, int isRoute)
{
  char *data, *str;
  double altfeet;
  struct tm tm;

  while (pdb_read_rec(file_in, NULL, NULL, NULL, (void **)&data) >= 0) {
    waypoint *wpt_tmp = waypt_new();
    int line = 0;
    char *tmp = data;


    if (global_opts.debug_level >= 5) {
      DBG(("\n\
--- BEGIN Input data record -----------------------------------------------\n\
%s\n\
--- END Input data record -------------------------------------------------\n",data));
    }

    while ((str = csv_lineparse(tmp, ",", "\"", line++))) {
      tmp = NULL;
      switch (line) {
      case 1:
        wpt_tmp->latitude = ppdb_decode_coord(str);
        break;
      case 2:
        wpt_tmp->longitude = ppdb_decode_coord(str);
        break;
      case 3:
        if (*str != '\0') {
          CHECK_INP(1, sscanf(str, "%lf", &altfeet), "altitude", str);
          if (altfeet != -9999) {
            wpt_tmp->altitude = FEET_TO_METERS(altfeet);
          }
        }
        break;
      case 4:
        memset(&tm, 0, sizeof(tm));
        if (ppdb_decode_tm(str, &tm)) {
          tm.tm_year -= 1900;
          tm.tm_mon--;
          wpt_tmp->creation_time = mkgmtime(&tm);
        }
        break;
      case 5:
        if (*str != '\0') {
          wpt_tmp->shortname = xstrdup(str);
        }
        break;
      case 6:
        if (*str != '\0') {
          wpt_tmp->icon_descr = xstrdup(str);
        }
        wpt_tmp->wpt_flags.icon_descr_is_dynamic = 1;
        break;
      case 7:
        if (*str != '\0') {
          wpt_tmp->notes = xstrdup(str);
        }
        break;

      }
    }


    if (warn_ && (global_opts.debug_level > 1) && (global_opts.debug_level < 5)) {
      warning("Faulty input data record : %s\n",data);
      warn_ = 0;
    }

    if (head && isRoute) {
      route_add_wpt(head, wpt_tmp);
    } else if (head) {
      track_add_wpt(head, wpt_tmp);
    } else {
      waypt_add(wpt_tmp);
    }

  }
  return 0;
}
