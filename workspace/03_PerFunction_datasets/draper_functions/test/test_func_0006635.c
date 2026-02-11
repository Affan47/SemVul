on_drawingarea1_motion_notify_event    (GtkWidget       *widget,
                                        GdkEventMotion  *event,
                                        gpointer         user_data)
{
	if(global_mapmode)
	{
		int x, y, width, height;
		GdkModifierType state;

		width  = map_drawable->allocation.width;
		height = map_drawable->allocation.height;

		if (event->is_hint)
			gdk_window_get_pointer (event->window, &x, &y, &state);
		else
		{
			x = event->x;
			y = event->y;
			state = event->state;
		}

		if (state & GDK_BUTTON1_MASK  && wtfcounter>=WTFCOUNTER)
		{
			GtkToggleToolButton *autocenter_toggle;

			if(!drag_started)
			{
				mouse_x = (int) event->x;
				mouse_y = (int) event->y;
				local_x = global_x;
				local_y = global_y;

				drag_started = 1;
			}
			global_autocenter = FALSE;

			mouse_dx = x - mouse_x;
			mouse_dy = y - mouse_y;

			gdk_draw_drawable (
				widget->window,
				widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
				pixmap,
				0,0,
				mouse_dx,mouse_dy,
				-1,-1);

			if(mouse_dx>0)
				gdk_draw_rectangle (
					widget->window,
					widget->style->white_gc,
					TRUE,
					0, 0,
					mouse_dx,
					widget->allocation.height);

			if (mouse_dy>0)
				gdk_draw_rectangle (
					widget->window,
					widget->style->white_gc,
					TRUE,
					0, 0,
					widget->allocation.width,
					mouse_dy);

			autocenter_toggle =
				GTK_TOGGLE_TOOL_BUTTON(lookup_widget(window1,
				                                     "button3"));
			gtk_toggle_tool_button_set_active(autocenter_toggle,
			                                  FALSE);

			autocenter_toggle =
				GTK_TOGGLE_TOOL_BUTTON(lookup_widget(window1,
				                                     "button56"));
			gtk_toggle_tool_button_set_active(autocenter_toggle,
			                                  FALSE);

		}
		else
			wtfcounter++;
	}

  return FALSE;
}
