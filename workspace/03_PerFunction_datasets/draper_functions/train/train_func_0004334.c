msroute_read_journey(void)
{
  int bufsz = 0;
  char* buff;

  buff = ole_read_property_stream(MSROUTE_OBJ_NAME, &bufsz);

  if ((buff != NULL) && (bufsz > 0)) {
    msroute_head_t* head = (msroute_head_t*)buff;
    unsigned char* cin, *cend;
    int count = 0;
    route_head* route;
    waypoint* wpt;
    char version;

    is_fatal((strncmp(head->masm, "MASM", 4) != 0), MYNAME ": Invalid or unknown data!");

    version = buff[0x14];
    is_fatal((version < 1) || (version > 7), MYNAME ": Unsupported version %d!", version);

    cin = (unsigned char*)buff + 71;
    cend = (unsigned char*)buff + bufsz;

    route = route_head_alloc();
    route_add_head(route);

    head->waypts = le_read32(&head->waypts);

    while (count < head->waypts) {
      int len;


      while (1) {
        len = *cin;
        if ((cin + 120) > cend) {
          cin = NULL;
          break;
        }
        if ((cin + len < cend) &&
            (cin[len + 3] == 0xff) &&
            (cin[len + 4] == len) &&
            (le_read16(cin + len + 1) == 0xfeff)) {
          break;
        }
        cin++;
      }
      if (cin == NULL) {
        break;
      }

      wpt = waypt_new();

      len = *cin++;
      cin += len;
      cin += 3;

      len = *cin++;
      wpt->shortname = cet_str_uni_to_utf8((const short*)cin, len);
      cin += (len * 2);
      cin += (5 * sizeof(gbint32));


      wpt->latitude = GPS_Math_Semi_To_Deg(le_read32(cin+12));
      wpt->longitude = GPS_Math_Semi_To_Deg(le_read32(cin+16));

      cin += (23 * sizeof(gbint32));
      cin += 3;

#ifdef OLE_DEBUG
      waypt_add(waypt_dupe(wpt));
#endif
      route_add_wpt(route, wpt);
      count++;
    }
  }

  if (buff != NULL) {
    xfree(buff);
  }
}
