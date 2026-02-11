write_tag_text(char *brivla, char *place, char *trans, int brac)
{
  char buffer[1024];

  if (brac) {
    sprintf(buffer, "%s%s (%s)", brivla, place, make_texsafe(trans));
  } else {
    sprintf(buffer, "%s%s %s", brivla, place, make_texsafe(trans));
  }
  if (tag_text[1]) {
    strcat(tag_text, "\n");
  }
  strcat(tag_text, buffer);
}
