build_frame_label(struct frame *frame)
{
	GtkWidget *label;

	label = label_in_box_new(frame->name ? frame->name : "(root)",
	    frame->name ? "Frame name. Click to select or edit." :
	    "Root frame. Click to select.");
	gtk_misc_set_padding(GTK_MISC(label), 2, 2);
	gtk_misc_set_alignment(GTK_MISC(label), 0, 0);

	label_in_box_bg(label, active_frame == frame ?
	    COLOR_FRAME_SELECTED : COLOR_FRAME_UNSELECTED);

	g_signal_connect(G_OBJECT(box_of_label(label)),
	    "button_press_event", G_CALLBACK(frame_press_event), frame);
	g_signal_connect(G_OBJECT(box_of_label(label)),
	    "button_release_event", G_CALLBACK(frame_release_event), frame);
	frame->label = label;

	if (frame != frames)
		setup_frame_drag(frame);

	return box_of_label(label);
}
