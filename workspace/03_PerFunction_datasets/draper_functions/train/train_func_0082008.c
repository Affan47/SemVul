screen_rect_to_layer_rect(struct gui_layer *gui_layer, SDL_Rect *dest_rect)
{
  if (gui_layer) {
    dest_rect->x = dest_rect->x - gui_layer->dest_rect.x;
    dest_rect->y = dest_rect->y - gui_layer->dest_rect.y;
  }
}
