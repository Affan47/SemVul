editor_end_selection_rectangle(int canvas_x, int canvas_y)
{
  int w, h;

  if (!editor) {
    return;
  }

  editor->selrect_active = FALSE;

  if (editor->selrect_width <= 0 || editor->selrect_height <= 0) {
    struct tile *ptile;

    ptile = canvas_pos_to_tile(canvas_x, canvas_y);
    if (ptile && editor->selection_mode == SELECTION_MODE_ADD) {
      editor_selection_add(ptile);
    } else if (ptile && editor->selection_mode == SELECTION_MODE_REMOVE) {
      editor_selection_remove(ptile);
    } else {
      recenter_button_pressed(canvas_x, canvas_y);
      return;
    }

    if (ptile) {
      refresh_tile_mapcanvas(ptile, TRUE, TRUE);
    }

    return;
  }

  gui_rect_iterate(mapview.gui_x0 + editor->selrect_x,
                   mapview.gui_y0 + editor->selrect_y,
                   editor->selrect_width, editor->selrect_height,
                   ptile, pedge, pcorner) {
    if (ptile == NULL) {
      continue;
    }
    if (editor->selection_mode == SELECTION_MODE_NEW
        || editor->selection_mode == SELECTION_MODE_ADD) {
      editor_selection_add(ptile);
    } else if (editor->selection_mode == SELECTION_MODE_REMOVE) {
      editor_selection_remove(ptile);
    }
  } gui_rect_iterate_end;

  w = tileset_tile_width(tileset);
  h = tileset_tile_height(tileset);

  update_map_canvas(editor->selrect_x - w,
                    editor->selrect_y - h,
                    editor->selrect_width + 2 * w,
                    editor->selrect_height + 2 * h);
  flush_dirty();
}
