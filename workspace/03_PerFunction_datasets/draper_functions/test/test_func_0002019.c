get_sprite_dimensions(struct sprite *sprite, int *width, int *height)
{
  *width = GET_SURF(sprite)->w;
  *height = GET_SURF(sprite)->h;
}
