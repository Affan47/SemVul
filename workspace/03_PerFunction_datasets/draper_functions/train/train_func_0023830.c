get_gp_from_db (GamePositionDb *db,
                gchar *id)
{
  GamePositionDbEntry *entry = gpdb_lookup(db, id);
  if (!entry) {
    g_test_message("The entry \"%s\" is missing from game position database.\n", id);
    g_test_fail();
  }
  g_assert(entry);
  return entry->game_position;
}
