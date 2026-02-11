read_tracks(const pdbfile* pdb)
{
  pdbrec_t* pdb_rec;
  int reclen, records, total, points, dropped;
  char descr[(2 * TRACK_POINT_SIZE) + 1];
  char temp_descr[TRACK_POINT_SIZE + 1];
  cetus_track_head_t* head;
  waypoint* wpt;
  route_head* track;
  time_t basetime;

  track = route_head_alloc();
  track_add_head(track);

  total = 0;
  points = 0;
  dropped = 0;
  basetime = 0;

  for (pdb_rec = pdb->rec_list; pdb_rec; pdb_rec = pdb_rec->next) {
    int i, magic;
    char* c = (char*)pdb_rec->data;

    magic = be_read32(c);
    if (magic != MYTRACK) {
      fatal(MYNAME ": Invaid track data or unsupported version!\n");
    }

    reclen = be_read32(c+4);
    records = reclen / TRACK_POINT_SIZE;

    c += 8;

    for (i = 0; i < records; i++, c += TRACK_POINT_SIZE) {
      switch (total++) {
        struct tm tm;

      case 0:
        head = (cetus_track_head_t*)c;
        if (head->id[0] != 'C' || head->id[1] != 'G') {
          fatal(MYNAME ": Invalid track header!\n");
        }

        memset(&tm, 0, sizeof(tm));
        tm.tm_mday = head->day;
        tm.tm_mon = head->month - 1;
        tm.tm_year = head->year + 100;
        basetime = mkgmtime(&tm);
        break;

      case 1:
        strncpy(descr, c, TRACK_POINT_SIZE);
        break;

      case 2:
        strncpy(temp_descr, c, TRACK_POINT_SIZE);
        strcat(descr, temp_descr);
        if (strlen(descr) > 0) {
          track->rte_desc = xstrdup(descr);
        }
        break;

      default:
        wpt = read_track_point((cetus_track_point_t*)c, basetime);
        if (wpt != NULL) {
          track_add_wpt(track, wpt);
          points++;
        } else {
          dropped++;
        }
      }

    }
  }

  if (global_opts.verbose_status > 0) {
    printf(MYNAME ": Loaded %d track point(s) from source.\n", points);
    if (dropped > 0) {
      printf(MYNAME ": ! %d dropped because of missing data (no time, no coordinates) !\n", dropped);
    }
  }
}
