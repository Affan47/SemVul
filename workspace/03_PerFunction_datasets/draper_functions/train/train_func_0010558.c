on_checkbox_toggle (GtkWidget *widget, gpointer data)
{
	AnimationInfo *animation_info = lookup_animation_info (widget);

	if (animation_info != NULL)
	{
		gfloat elapsed = g_timer_elapsed (animation_info->timer, NULL);
		animation_info->start_modifier = elapsed - animation_info->start_modifier;
		animation_info->starting_state_type = GTK_STATE_ACTIVE;
	}
	else
	{
		add_animation (widget, CHECK_ANIMATION_TIME, GTK_STATE_ACTIVE, 0);
	}
}
