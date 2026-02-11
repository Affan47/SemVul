nmn4_read_data(void)
{
  char* buff;
  char* str, *c;
  int column;
  int line = 0;

  char* zip1, *zip2, *city, *street, *number;
  route_head* route;
  waypoint* wpt;

  route = route_head_alloc();
  route_add_head(route);

  while ((buff = gbfgetstr(fin))) {
    if ((line++ == 0) && fin->unicode) {
      cet_convert_init(CET_CHARSET_UTF8, 1);
    }
    str = buff = lrtrim(buff);
    if (*buff == '\0') {
      continue;
    }

    nmn4_check_line(buff);


    zip1 = zip2 = city = street = number = NULL;

    wpt = waypt_new();

    column = -1;
    c = csv_lineparse(str, "|", "", column++);
    while (c != NULL) {
      switch (column) {
      case  0:
      case  1:
      case  2:
      case  3:
      case  9:
      case 10:
      case 13:
      case 14:
      case 15:
        break;

      case  4:
        if (*c != '-') {
          zip1 = xstrdup(c);
        } else {
          zip1 = xstrdup("");
        }
        break;

      case  5:
        if (*c != '-') {
          city = xstrdup(c);
        } else {
          city = xstrdup("");
        }
        break;

      case  6:
        if (*c != '-') {
          zip2 = xstrdup(c);
        } else {
          zip2 = xstrdup("");
        }
        break;

      case  7:
        if (*c != '-') {
          street = xstrdup(c);
        } else {
          street = xstrdup("");
        }
        break;

      case  8:
        if (*c != '-') {
          number = xstrdup(c);
        } else {
          number = xstrdup("");
        }


        if (strcmp(zip1, zip2) == 0) {
          *zip2 = '\0';
        }
        if (*city != '\0') {


          if ((*street != '\0') || (*number != '\0') || (*zip2 != '\0')) {
            city = xstrappend(city, ",");
          }
        }


        wpt->description = nmn4_concat(zip1, city, street, number, zip2, NULL);
        break;

      case 11:
        sscanf(c, "%lf", &wpt->longitude);
        break;

      case 12:
        sscanf(c, "%lf", &wpt->latitude);
        break;

      }
      c = csv_lineparse(NULL, "|", "", column++);
    }
    route_add_wpt(route, wpt);
  }
}
