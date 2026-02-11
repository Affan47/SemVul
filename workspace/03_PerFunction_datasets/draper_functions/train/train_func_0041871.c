node_rectangle_minimum_size(struct tree_node *node,
					int *width, int *height)
{
  int max_icon_height;
  int icons_width_sum;
  struct sprite* sprite;
  int swidth, sheight;

  if (node->is_dummy) {

    *width = *height = 1;
  } else {
    get_text_size(width, height, FONT_REQTREE_TEXT,
		  advance_name_for_player(client.conn.playing, node->tech));
    *width += 2;
    *height += 8;

    max_icon_height = 0;
    icons_width_sum = 5;

    if (reqtree_show_icons) {

      unit_type_iterate(unit) {
        if (advance_number(unit->require_advance) != node->tech) {
          continue;
        }
        sprite = get_unittype_sprite(tileset, unit, direction8_invalid(),
                                     TRUE);
        get_sprite_dimensions(sprite, &swidth, &sheight);
        max_icon_height = MAX(max_icon_height, sheight);
        icons_width_sum += swidth + 2;
      } unit_type_iterate_end;


      improvement_iterate(pimprove) {
        requirement_vector_iterate(&(pimprove->reqs), preq) {
          if (VUT_ADVANCE == preq->source.kind
	   && advance_number(preq->source.value.advance) == node->tech) {
	    sprite = get_building_sprite(tileset, pimprove);

            if (sprite) {
              get_sprite_dimensions(sprite, &swidth, &sheight);
              max_icon_height = MAX(max_icon_height, sheight);
              icons_width_sum += swidth + 2;
            }
	  }
        } requirement_vector_iterate_end;
      } improvement_iterate_end;


      governments_iterate(gov) {
        requirement_vector_iterate(&(gov->reqs), preq) {
          if (VUT_ADVANCE == preq->source.kind
	   && advance_number(preq->source.value.advance) == node->tech) {
            sprite = get_government_sprite(tileset, gov);
	    get_sprite_dimensions(sprite, &swidth, &sheight);
            max_icon_height = MAX(max_icon_height, sheight);
            icons_width_sum += swidth + 2;
	  }
        } requirement_vector_iterate_end;
      } governments_iterate_end;
    }

    *height += max_icon_height;
    if (*width < icons_width_sum) {
      *width = icons_width_sum;
    }
  }
}
