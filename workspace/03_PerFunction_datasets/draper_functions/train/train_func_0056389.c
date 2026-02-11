sv_detach_control (SheetControl *sc)
{
	g_return_if_fail (IS_SHEET_CONTROL (sc));
	g_return_if_fail (IS_SHEET_VIEW (sc->view));

	g_ptr_array_remove (sc->view->controls, sc);
	if (sc->view->controls->len == 0) {
		g_ptr_array_free (sc->view->controls, TRUE);
		sc->view->controls = NULL;
	}
	sc->view = NULL;
}
