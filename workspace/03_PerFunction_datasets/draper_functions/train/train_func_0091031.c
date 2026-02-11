id3_show_tag (ID3_tag *tag, char *fn)
{
  user_message(FALSE, "===> %s:\n", fn);

  if (strlen(tag->songname) > 0)
    user_message(FALSE, "Song Name: %s\n", tag->songname);

  if (strlen(tag->artist) > 0)
    user_message(FALSE, "   Artist: %s\n", tag->artist);

  if (strlen(tag->album) > 0)
    user_message(FALSE, "    Album: %s\n", tag->album);

  if (strlen(tag->year) > 0)
    user_message(FALSE, "     Year: %s\n", tag->year);

  if (strlen(tag->u.v10.comment) > 0)
    user_message(FALSE, "  Comment: %s\n", tag->u.v10.comment);

  if (tag->version == 1 && tag->u.v11.track !=0)
    user_message(FALSE, "    Track: %02d\n", tag->u.v11.track);

  if (tag->genre >= 0 && tag->genre < genre_count)
    user_message(FALSE, "    Genre: %s\n", genre_table[tag->genre]);

  user_message(FALSE, "\n");
}
