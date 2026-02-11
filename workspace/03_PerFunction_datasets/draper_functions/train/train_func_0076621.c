cb_rotation_changed (GtkSpinButton *spin, GogAxis *axis)
{
	axis->circular_rotation = CLAMP (gtk_spin_button_get_value (spin),
					 GOG_AXIS_CIRCULAR_ROTATION_MIN,
					 GOG_AXIS_CIRCULAR_ROTATION_MAX);
	gog_object_emit_changed (GOG_OBJECT (axis), TRUE);
}
