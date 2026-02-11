load_and_setup_sound_track (a_sound_track* st)
{
  if (st) {
    load_soundtrack (st->filename);
    soundtrack_title = st->title;
    soundtrack_author = st->author;
    last_rank = st->rank;
  } else {
    soundtrack_title = 0;
    soundtrack_author = 0;
  }
  FREE_SPRITE0 (soundtrack_title_sprite);
  FREE_SPRITE0 (soundtrack_author_sprite);
}
