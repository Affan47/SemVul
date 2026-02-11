update_max_unit_size(void)
{
  max_unit_height = 0;
  max_unit_width = 0;

  unit_type_iterate(i) {
    int x1, x2, y1, y2;
    struct sprite *sprite = get_unittype_sprite(tileset, i,
                                                direction8_invalid(), TRUE);

    sprite_get_bounding_box(sprite, &x1, &y1, &x2, &y2);
    max_unit_width = MAX(max_unit_width, x2 - x1);
    max_unit_height = MAX(max_unit_height, y2 - y1);
  } unit_type_iterate_end;
}
