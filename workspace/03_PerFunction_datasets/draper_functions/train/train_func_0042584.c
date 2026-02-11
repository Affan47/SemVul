Read_AN1_Waypoints(gbfile* f)
{
  unsigned long count = 0;
  unsigned long i = 0;
  an1_waypoint_record* rec = NULL;
  waypoint* wpt_tmp;
  char* icon = NULL;
  char* url = NULL;
  ReadShort(f);
  count = ReadLong(f);
  for (i = 0; i < count; i++) {
    rec = Alloc_AN1_Waypoint();
    Read_AN1_Waypoint(f, rec);
    wpt_tmp = waypt_new();

    if (rec->creation_time) {
      wpt_tmp->creation_time = rec->creation_time;
    }
    wpt_tmp->longitude = -DecodeOrd(rec->lon);
    wpt_tmp->latitude = DecodeOrd(rec->lat);
    wpt_tmp->notes = xstrdup(rec->comment);
    wpt_tmp->description = xstrdup(rec->name);
    if (rec->url) {
      wpt_tmp->url = xstrdup(rec->url);
    } else if (NULL != (url=strstr(wpt_tmp->description, "{URL="))) {
      *url = '\0';
      url += 5;
      url[strlen(url)-1] = '\0';
      wpt_tmp->url = xstrdup(url);
    }

    if (rec->image_name) {
      wpt_tmp->icon_descr = xstrdup(rec->image_name);
    } else if (FindIconByGuid(&rec->guid, &icon)) {
      wpt_tmp->icon_descr = icon;
    }

    fs_chain_add(&(wpt_tmp->fs), (format_specific_data*)rec);
    rec = NULL;
    waypt_add(wpt_tmp);
  }
}
