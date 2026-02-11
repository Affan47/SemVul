gtk_color_wheel_motion_notify(GtkWidget *widget, GdkEventMotion *event){
	GtkColorWheelPrivate *ns = GTK_COLOR_WHEEL_GET_PRIVATE(widget);

    if (ns->grab_active){
		double dx = -((event->x - widget->style->xthickness) - ns->radius);
		double dy = (event->y - widget->style->ythickness) - ns->radius;

		double angle = atan2(dx, dy) + M_PI;

		ns->grab_active->hue = angle / (M_PI * 2);

		g_signal_emit(widget, gtk_color_wheel_signals[HUE_CHANGED], 0, get_color_index(ns, ns->grab_active));

		gtk_widget_queue_draw(widget);

		return true;
	}else if (ns->grab_block){

		double dx = (event->x - widget->style->xthickness) - ns->radius + ns->block_size / 2;
		double dy = (event->y - widget->style->ythickness) - ns->radius + ns->block_size / 2;

		ns->selected->saturation = clamp_float(dx / ns->block_size, 0, 1);
		ns->selected->lightness = clamp_float(dy / ns->block_size, 0, 1);

		g_signal_emit(widget, gtk_color_wheel_signals[SATURATION_VALUE_CHANGED], 0, get_color_index(ns, ns->selected));

		gtk_widget_queue_draw(widget);
		return true;
	}


	return false;
}
