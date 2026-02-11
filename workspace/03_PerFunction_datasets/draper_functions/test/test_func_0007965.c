sbadd1(SB *sb, char c)
{
  sbgrow(sb, 1);
  if (sb->buffer)
    sb->buffer[sb->len++] = c;
}
