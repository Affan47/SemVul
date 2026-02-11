popup_properties(struct tile *ptile)
{
  struct tile_list *tiles;

  if (!ptile) {
    return;
  }

  tiles = tile_list_new();

  if (editor_tile_is_selected(ptile)) {
    tile_hash_iterate(editor->selected_tile_table, sel_tile) {
      if (can_edit_tile_properties(sel_tile)) {
        tile_list_append(tiles, sel_tile);
      }
    } tile_hash_iterate_end;
  } else {
    if (can_edit_tile_properties(ptile)) {
      tile_list_append(tiles, ptile);
    }
  }

  editgui_popup_properties(tiles, NUM_OBJTYPES);

  tile_list_destroy(tiles);
}
