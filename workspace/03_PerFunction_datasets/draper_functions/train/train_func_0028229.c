uninit_tile_sprites (void)
{
  while (tile_set_size--)
    XFREE0 (tile_transp[tile_set_size]);
  XFREE0 (tile_transp);
}
