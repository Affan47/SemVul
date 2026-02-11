player_description_test (void)
{

  g_assert(g_strcmp0(player_description(BLACK_PLAYER), "The Black player") == 0);
  g_assert(g_strcmp0(player_description(WHITE_PLAYER), "The White player") == 0);

}
