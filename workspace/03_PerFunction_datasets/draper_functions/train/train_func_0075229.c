layout_key_press_cb(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
	LayoutWindow *lw = data;
	gboolean stop_signal = FALSE;
	gint x = 0;
	gint y = 0;

#if GTK_CHECK_VERSION(2,20,0)
	if (lw->path_entry && gtk_widget_has_focus(lw->path_entry))
#else
	if (lw->path_entry && GTK_WIDGET_HAS_FOCUS(lw->path_entry))
#endif
		{
		if (event->keyval == GDK_Escape && lw->dir_fd)
			{
			gtk_entry_set_text(GTK_ENTRY(lw->path_entry), lw->dir_fd->path);
			}


		if (gtk_widget_event(lw->path_entry, (GdkEvent *)event))
			{
			return TRUE;
			}
		}
#if GTK_CHECK_VERSION(2,20,0)
	if (lw->vd && lw->options.dir_view_type == DIRVIEW_TREE && gtk_widget_has_focus(lw->vd->view) &&
#else
	if (lw->vd && lw->options.dir_view_type == DIRVIEW_TREE && GTK_WIDGET_HAS_FOCUS(lw->vd->view) &&
#endif
	    !layout_key_match(event->keyval) &&
	    gtk_widget_event(lw->vd->view, (GdkEvent *)event))
		{
		return TRUE;
		}
	if (lw->bar &&
	    bar_event(lw->bar, (GdkEvent *)event))
		{
		return TRUE;
		}


	if (lw->image &&
#if GTK_CHECK_VERSION(2,20,0)
	    (gtk_widget_has_focus(lw->image->widget) || (lw->tools && widget == lw->window) || lw->full_screen) )
#else
	    (GTK_WIDGET_HAS_FOCUS(lw->image->widget) || (lw->tools && widget == lw->window) || lw->full_screen) )
#endif
		{
		stop_signal = TRUE;
		switch (event->keyval)
			{
			case GDK_Left: case GDK_KP_Left:
				x -= 1;
				break;
			case GDK_Right: case GDK_KP_Right:
				x += 1;
				break;
			case GDK_Up: case GDK_KP_Up:
				y -= 1;
				break;
			case GDK_Down: case GDK_KP_Down:
				y += 1;
				break;
			default:
				stop_signal = FALSE;
				break;
			}

		if (!stop_signal &&
		    !(event->state & GDK_CONTROL_MASK))
			{
			stop_signal = TRUE;
			switch (event->keyval)
				{
				case GDK_Menu:
					layout_image_menu_popup(lw);
					break;
				default:
					stop_signal = FALSE;
					break;
				}
			}
		}

	if (x != 0 || y!= 0)
		{
		keyboard_scroll_calc(&x, &y, event);
		layout_image_scroll(lw, x, y, (event->state & GDK_SHIFT_MASK));
		}

	return stop_signal;
}
