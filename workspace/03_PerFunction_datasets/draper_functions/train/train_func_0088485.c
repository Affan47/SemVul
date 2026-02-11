pkg_scroll_event(GtkWidget *widget, GdkEventScroll *event,
    gpointer data)
{
	struct pkg *pkg, *last;

	switch (event->direction) {
	case GDK_SCROLL_UP:
		if (active_pkg->next)
			active_pkg = active_pkg->next;
		else
			active_pkg = pkgs->next;
		change_world();
		break;
	case GDK_SCROLL_DOWN:
		last = NULL;
		for (pkg = pkgs->next; pkg && (!last || pkg != active_pkg);
		    pkg = pkg->next)
			last = pkg;
		active_pkg = last;
		change_world();
		break;
	default:
		;
	}
	return TRUE;
}
