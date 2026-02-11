on_anim_transition_scale_changed(GtkWidget *widget, gpointer user_data) {


    double v;
    Explorer *self = EXPLORER(user_data);
    GtkTreeIter iter;
    gdouble keyframe_duration;

    self->seeking_animation_transition = TRUE;

    if (!self->seeking_animation) {
	v = gtk_range_get_adjustment(GTK_RANGE(widget))->value;
	explorer_get_current_keyframe(self, &iter);

	gtk_tree_model_get(GTK_TREE_MODEL(self->animation->model), &iter,
			   ANIMATION_MODEL_DURATION, &keyframe_duration,
			   -1);


	gtk_range_set_value(GTK_RANGE(glade_xml_get_widget(self->xml, "anim_scale")),
			    animation_keyframe_get_time(self->animation, &iter) +
			    v * keyframe_duration * 0.9999 + 0.00001);
    }

    self->seeking_animation_transition = FALSE;
}
