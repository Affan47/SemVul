inv_display_err_motion_notify_event(GtkWidget *widget, GdkEventMotion *event)
{
	g_assert(INV_IS_DISPLAY_ERR(widget));
	switch(INV_DISPLAY_ERR(widget)->active_dot) {
		case INV_DISPLAY_ERR_DOT_SOURCE:
			inv_display_err_update_active_dot(INV_DISPLAY_ERR_DOT_SOURCE,
							INV_DISPLAY_ERR(widget)->room[INV_DISPLAY_ERR_ROOM_LENGTH],
							INV_DISPLAY_ERR(widget)->room[INV_DISPLAY_ERR_ROOM_WIDTH],
							event->x,
							event->y,
							&(INV_DISPLAY_ERR(widget)->source[INV_DISPLAY_ERR_LR]),
							&(INV_DISPLAY_ERR(widget)->source[INV_DISPLAY_ERR_FB]));
			inv_display_err_paint(widget,INV_DISPLAY_ERR_DRAW_DATA);
			return FALSE;
			break;
		case INV_DISPLAY_ERR_DOT_DEST:
			inv_display_err_update_active_dot(INV_DISPLAY_ERR_DOT_DEST,
							INV_DISPLAY_ERR(widget)->room[INV_DISPLAY_ERR_ROOM_LENGTH],
							INV_DISPLAY_ERR(widget)->room[INV_DISPLAY_ERR_ROOM_WIDTH],
							event->x,
							event->y,
							&(INV_DISPLAY_ERR(widget)->dest[INV_DISPLAY_ERR_LR]),
							&(INV_DISPLAY_ERR(widget)->dest[INV_DISPLAY_ERR_FB]));
			inv_display_err_paint(widget,INV_DISPLAY_ERR_DRAW_DATA);
			return FALSE;
			break;
	}
	return TRUE;

}
