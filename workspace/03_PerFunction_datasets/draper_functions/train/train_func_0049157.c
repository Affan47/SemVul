tpo_process_symbols(void)
{
  unsigned int waypoint_count;
  unsigned int ii;


  if (tpo_find_block(0x040000)) {
    return;
  }


  waypoint_count = tpo_read_int();


  if (!waypoint_count) {
    return;
  }


  for (ii = 0; ii < waypoint_count; ii++) {
    int lat;
    int lon;
    char *waypoint_name;
    waypoint* waypoint_temp;


    (void)tpo_read_int();


    (void)tpo_read_int();

    lon = gbfgetint32(tpo_file_in);
    lat = gbfgetint32(tpo_file_in);


    waypoint_temp = tpo_convert_ll(lat, lon);


    waypoint_name = (char *) xmalloc(15);
    sprintf(waypoint_name, "SYM %d", ii+1);

    waypoint_temp->shortname = waypoint_name;


    waypt_add(waypoint_temp);
  }
}
