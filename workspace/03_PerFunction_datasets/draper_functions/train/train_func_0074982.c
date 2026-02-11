tpo_process_map_notes(void)
{
  unsigned int waypoint_count;
  unsigned int ii;


  if (tpo_find_block(0x090000)) {
    return;
  }


  waypoint_count = tpo_read_int();


  if (!waypoint_count) {
    return;
  }


  for (ii = 0; ii < waypoint_count; ii++) {
    int lat;
    int lon;
    unsigned int name_length;
    char *waypoint_name;
    waypoint* waypoint_temp;
    unsigned int num_bytes;
    unsigned int jj;


    (void)tpo_read_int();

    lon = gbfgetint32(tpo_file_in);
    lat = gbfgetint32(tpo_file_in);


    waypoint_temp = tpo_convert_ll(lat, lon);


    waypoint_name = (char *) xmalloc(15);
    sprintf(waypoint_name, "NOTE %d", ii+1);

    waypoint_temp->shortname = waypoint_name;


    (void)tpo_read_int();


    (void)tpo_read_int();


    (void)tpo_read_int();


    name_length = tpo_read_int();
    if (name_length) {
      char *comment;

      comment = (char *) xmalloc(name_length+1);
      comment[0] = '\0';
      gbfread(comment, 1, name_length, tpo_file_in);
      comment[name_length] = '\0';
      waypoint_temp->description = comment;

    } else {

    }


    name_length = tpo_read_int();

    if (name_length) {
      char *notes;

      notes = (char *) xmalloc(name_length+1);
      notes[0] = '\0';
      gbfread(notes, 1, name_length, tpo_file_in);
      notes[name_length] = '\0';
      waypoint_temp->url = notes;

    }


    name_length = tpo_read_int();
    if (name_length) {
      char *notes;

      notes = (char *) xmalloc(name_length+1);
      notes[0] = '\0';
      gbfread(notes, 1, name_length, tpo_file_in);
      notes[name_length] = '\0';
      waypoint_temp->url = notes;

    }


    (void)tpo_read_int();


    (void)tpo_read_int();


    num_bytes = tpo_read_int();

    for (jj = 0; jj < num_bytes; jj++) {
      (void) gbfgetc(tpo_file_in);
    }


    (void)tpo_read_int();


    (void)tpo_read_int();


    waypt_add(waypoint_temp);
  }
}
