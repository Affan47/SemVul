gnm_pane_special_cursor_stop (GnmPane *pane)
{
	g_return_if_fail (pane->cursor.special != NULL);

	g_clear_object (&pane->cursor.special);
}
