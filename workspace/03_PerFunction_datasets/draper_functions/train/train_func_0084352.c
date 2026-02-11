do_toggle_reason(int ix, enum toggle_type reason)
{
	struct toggle *t = &appres.toggle[ix];


	toggle_toggle(t);
	if (t->upcall != NULL)
		t->upcall(t, reason);
#if defined(X3270_MENUS)
	menubar_retoggle(t);
#endif
}
