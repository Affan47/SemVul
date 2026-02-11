tileset_free_tiles(struct tileset *t)
{
  log_debug("tileset_free_tiles()");

  unload_all_sprites(t);

  free_city_sprite(t->sprites.city.tile);
  t->sprites.city.tile = NULL;
  free_city_sprite(t->sprites.city.wall);
  t->sprites.city.wall = NULL;
  free_city_sprite(t->sprites.city.occupied);
  t->sprites.city.occupied = NULL;

  if (t->sprite_hash) {
    sprite_hash_destroy(t->sprite_hash);
    t->sprite_hash = NULL;
  }

  small_sprite_list_iterate(t->small_sprites, ss) {
    small_sprite_list_remove(t->small_sprites, ss);
    if (ss->file) {
      free(ss->file);
    }
    fc_assert(ss->sprite == NULL);
    free(ss);
  } small_sprite_list_iterate_end;

  specfile_list_iterate(t->specfiles, sf) {
    specfile_list_remove(t->specfiles, sf);
    free(sf->file_name);
    if (sf->big_sprite) {
      free_sprite(sf->big_sprite);
      sf->big_sprite = NULL;
    }
    free(sf);
  } specfile_list_iterate_end;

  sprite_vector_iterate(&t->sprites.city.worked_tile_overlay, psprite) {
    free_sprite(*psprite);
  } sprite_vector_iterate_end;
  sprite_vector_free(&t->sprites.city.worked_tile_overlay);

  sprite_vector_iterate(&t->sprites.city.unworked_tile_overlay, psprite) {
    free_sprite(*psprite);
  } sprite_vector_iterate_end;
  sprite_vector_free(&t->sprites.city.unworked_tile_overlay);

  if (t->sprites.tx.fullfog) {
    free(t->sprites.tx.fullfog);
    t->sprites.tx.fullfog = NULL;
  }

  sprite_vector_free(&t->sprites.colors.overlays);
  sprite_vector_free(&t->sprites.explode.unit);
  sprite_vector_free(&t->sprites.nation_flag);
  sprite_vector_free(&t->sprites.nation_shield);
  sprite_vector_free(&t->sprites.citybar.occupancy);

  tileset_background_free(t);
}
