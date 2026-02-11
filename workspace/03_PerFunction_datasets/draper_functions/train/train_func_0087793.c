_e2_ownership_dialog_toggle_recurse_button_cb
	(GtkToggleButton *togglebutton, E2_OwnersDldRuntime *rt)
{
	if (rt->permission)
		rt->recurse = GTK_TOGGLE_BUTTON (rt->recurse_dirs_button)->active;
	return;
}
