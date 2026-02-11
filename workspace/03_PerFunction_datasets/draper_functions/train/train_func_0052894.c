test_win (GooCanvasItem **board)
{
  int i;

  for (i = 0; i < 15; i++)
    if (!board[i] || (GPOINTER_TO_INT (g_object_get_data (G_OBJECT (board[i]), "piece_num")) != i))
      return;


  gamewon = TRUE;
  fifteen_destroy_all_items();
  gc_bonus_display(gamewon, GC_BONUS_SMILEY);

}
