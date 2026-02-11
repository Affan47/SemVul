non_terminal_string (char *buf, int att)
{
  if (att > 0 && att < WILDCARD) {
    if (attribute_names[att] != NO_TEXT) {
      char *q = buf;
      bufcpy (q, attribute_names[att], BUFFER_SIZE);
      while (q[0] != NULL_CHAR) {
        if (q[0] == '_') {
          q[0] = '-';
        } else {
          q[0] = (char) TO_LOWER (q[0]);
        }
        q++;
      }
      return (buf);
    } else {
      return (NO_TEXT);
    }
  } else {
    return (NO_TEXT);
  }
}
