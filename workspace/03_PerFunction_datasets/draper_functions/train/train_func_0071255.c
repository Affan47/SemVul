iktobj_trkpt(const char* args, const char** attrv)
{
  const char** avp = &attrv[0];

  waypt = waypt_new();
  while (*avp) {
    if (strcmp(avp[0], "X") == 0) {
      waypt->longitude = atof(avp[1]);
    } else if (strcmp(avp[0], "Y") == 0) {
      waypt->latitude = atof(avp[1]);
    }
    avp+=2;
  }
  track_add_wpt(track, waypt);
  waypt = NULL;
}
