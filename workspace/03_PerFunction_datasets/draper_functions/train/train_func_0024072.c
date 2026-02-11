blit_all_item_slots(int mask)
{
	int i;
	struct visible_level *vis_lvl, *n;

	if (mask & OMIT_ITEMS_LABEL) {

		return;
	}

	BROWSE_VISIBLE_LEVELS(vis_lvl, n) {

		level *item_level = vis_lvl->lvl_pointer;

		for (i = 0; i < MAX_ITEMS_PER_LEVEL; i++) {


			if (item_level->ItemList[i].type == (-1))
				continue;


			if (MouseCursorIsInRect(&(item_level->ItemList[i].text_slot_rectangle), GetMousePos_x(), GetMousePos_y()))
				draw_rectangle(&item_level->ItemList[i].text_slot_rectangle, 0, 0, 153, 100);
			else {
				if ((item_level->ItemList[i].text_slot_rectangle.x + item_level->ItemList[i].text_slot_rectangle.w <= 0) ||
					(item_level->ItemList[i].text_slot_rectangle.y + item_level->ItemList[i].text_slot_rectangle.h <= 0) ||
					(item_level->ItemList[i].text_slot_rectangle.x >= GameConfig.screen_width) ||
					(item_level->ItemList[i].text_slot_rectangle.y >= GameConfig.screen_height))
					continue;

				draw_rectangle(&item_level->ItemList[i].text_slot_rectangle, 0, 0, 0, BACKGROUND_TEXT_RECT_ALPHA);
			}


			PutStringFont(Screen, FPS_Display_BFont, item_level->ItemList[i].text_slot_rectangle.x,
					  item_level->ItemList[i].text_slot_rectangle.y, D_(ItemMap[item_level->ItemList[i].type].item_name));

		}
	}
}
