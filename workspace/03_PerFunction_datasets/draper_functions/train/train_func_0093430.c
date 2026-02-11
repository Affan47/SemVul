sdlkeyboard_init(void)
{
  keysyms_map_t *ptr3;

  unicode_keysyms_hash = g_hash_table_new( g_int_hash, g_int_equal );

  for( ptr3 = (keysyms_map_t *)unicode_keysyms_map; ptr3->ui; ptr3++ )
    g_hash_table_insert( unicode_keysyms_hash, &( ptr3->ui ),
                         &( ptr3->fuse ) );

  SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
}
