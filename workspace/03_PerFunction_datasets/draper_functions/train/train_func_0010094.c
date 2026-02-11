sc_sheet (SheetControl const *sc)
{
	g_return_val_if_fail (IS_SHEET_CONTROL (sc), NULL);
	return sc->view ? sc->view->sheet : NULL;
}
