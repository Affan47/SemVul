on_anim_curve_changed(GtkWidget *widget, gpointer user_data) {


    Explorer *self = EXPLORER(user_data);
    GtkTreeIter iter;
    Spline *spline;

    if (!self->allow_transition_changes)
	return;

    explorer_get_current_keyframe(self, &iter);

    spline = curve_editor_get_spline(CURVE_EDITOR(self->anim_curve));
    gtk_list_store_set(self->animation->model, &iter,
		       ANIMATION_MODEL_SPLINE, spline,
		       -1);
    spline_free(spline);
}
