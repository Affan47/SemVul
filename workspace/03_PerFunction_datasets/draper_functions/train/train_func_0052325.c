_make_menu_entry(menu_item_t *item, int offset, int width, gfxw_port_t *port, gfx_color_t color, gfx_color_t bgcolor, int ID, int gray)
{
	rect_t area		= gfx_rect(MENU_BOX_LEFT_PADDING, 0, width - MENU_BOX_LEFT_PADDING, 10);
	rect_t list_area	= gfx_rect(port->zone.x, area.y + offset + port->zone.y, width, area.yl);
	gfxw_list_t *list	= (gfxw_list_t *) gfxw_set_id(GFXW(gfxw_new_list(list_area, 0)), ID, GFXW_NO_ID);
	gfx_color_t xcolor	= {0};

	color = un_prioritize(color);
	bgcolor = un_prioritize(bgcolor);

	xcolor = gray? color : bgcolor;

	list->add(GFXWC(list), GFXW(gfxw_new_box(port->visual->gfx_state, area, bgcolor, bgcolor, GFX_BOX_SHADE_FLAT)));
	list->add(GFXWC(list), GFXW(gfxw_new_text(port->visual->gfx_state, area, port->font_nr, item->text, ALIGN_LEFT, ALIGN_CENTER,
						  color, xcolor, bgcolor, GFXR_FONT_FLAG_NO_NEWLINES)));

	if (item->keytext) {
		area.xl -= MENU_BOX_RIGHT_PADDING;
		list->add(GFXWC(list), GFXW(gfxw_new_text(port->visual->gfx_state, area, port->font_nr, item->keytext, ALIGN_RIGHT, ALIGN_CENTER,
						     color, xcolor, bgcolor, GFXR_FONT_FLAG_NO_NEWLINES)));
	}

	return GFXW(list);
}
