dc_load_tile(int script, int* yield, int* preturnint, char* tileset_file, int tileset_index)
{

  if (tileset_index >= 1 && tileset_index <= GFX_TILES_NB_SETS)
    {

      tiles_load_slot(tileset_file, tileset_index);


      strncpy(play.tile[tileset_index].file, tileset_file, 50);
    }
  else
    {
      log_error("[DinkC] %s:%d:%s: dc_load_tile: invalid tileset index '%d'",
		rinfo[script]->name, rinfo[script]->debug_line, cur_funcname,
		tileset_index);
    }
}
