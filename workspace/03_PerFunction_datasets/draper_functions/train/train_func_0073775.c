frame_ref_select_event(GtkWidget *widget, GdkEventButton *event,
    gpointer data)
{
	struct obj *obj = data;

	switch (event->button) {
	case 1:
		obj->u.frame.ref->active_ref = data;
		change_world();
		break;
	}
	return TRUE;
}
