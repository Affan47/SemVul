Parse_Change_Type(char* type)
{
  long retval = 0x11100541;

  if (!case_ignore_strcmp(type, "limited")) {
    retval = 0x11070430;
  } else if (!case_ignore_strcmp(type, "toll")) {
    retval = 0x11070470;
  } else if (!case_ignore_strcmp(type, "us")) {
    retval = 0x11070870;
  } else if (!case_ignore_strcmp(type, "state")) {
    retval = 0x11070c10;
  } else if (!case_ignore_strcmp(type, "primary")) {

    retval = 0x11070840;
  } else if (!case_ignore_strcmp(type, "major")) {
    retval = 0x11070c30;
  } else if (!case_ignore_strcmp(type, "local")) {
    retval = 0x11071010;
  } else if (!case_ignore_strcmp(type, "ramp")) {
    retval = 0x11070cb0;
  } else if (!case_ignore_strcmp(type, "ferry")) {
    retval = 0x11070ca0;
  } else if (!case_ignore_strcmp(type, "editable")) {
    retval = 0x11100541;
  } else {
    fatal(MYNAME ": unknown road type for road changes\n");
  }
  return retval;
}
