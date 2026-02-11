dirty_rect(int canvas_x, int canvas_y,
                int pixel_width, int pixel_height)
{
  if (mapview_is_frozen()) {
    return;
  }
  if (num_dirty_rects < MAX_DIRTY_RECTS) {
    dirty_rects[num_dirty_rects].x = canvas_x;
    dirty_rects[num_dirty_rects].y = canvas_y;
    dirty_rects[num_dirty_rects].width = pixel_width;
    dirty_rects[num_dirty_rects].height = pixel_height;
    num_dirty_rects++;
    queue_flush();
  }
}
