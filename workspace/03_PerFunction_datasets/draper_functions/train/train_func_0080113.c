Init_Wpt_Type(void)
{
  if (!opt_wpt_type || !opt_wpt_type[0]) {
    wpt_type_num = 1;
    return;
  }
  if ((opt_wpt_type[0] & 0xf0) == 0x30) {
    wpt_type_num = atoi(opt_wpt_type);
  } else {
    wpt_type_num = 1;
    if (!case_ignore_strcmp(opt_wpt_type, "marker")) {
      wpt_type_num = 1;
    } else if (!case_ignore_strcmp(opt_wpt_type, "symbol")) {
      wpt_type_num = 1;
    } else if (!case_ignore_strcmp(opt_wpt_type, "text")) {
      wpt_type_num = 4;
    } else if (!case_ignore_strcmp(opt_wpt_type, "mapnote")) {
      wpt_type_num = 6;
    } else if (!case_ignore_strcmp(opt_wpt_type, "circle")) {
      wpt_type_num = 5;
    } else if (!case_ignore_strcmp(opt_wpt_type, "image")) {
      wpt_type_num = 18;
    } else {
      fatal(MYNAME ": wpt_type must be "
            "symbol, text, mapnote, circle, or image\n");
    }
  }
}
