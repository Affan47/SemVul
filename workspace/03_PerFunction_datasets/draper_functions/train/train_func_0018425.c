scrollBar()
{
	GtkPolicyType h, v;
	int ret = 3;

	if (!_scroll)
		return 0;

	gtk_scrolled_window_get_policy(_scroll, &h, &v);
	if (h == GTK_POLICY_NEVER) ret--;
	if (v == GTK_POLICY_NEVER) ret -= 2;

	return ret;
}
