hitori_free_board (Hitori *hitori)
{
	guint i;

	if (hitori->board == NULL)
		return;

	for (i = 0; i < hitori->board_size; i++)
		g_slice_free1 (sizeof (HitoriCell) * hitori->board_size, hitori->board[i]);
	g_free (hitori->board);
}
