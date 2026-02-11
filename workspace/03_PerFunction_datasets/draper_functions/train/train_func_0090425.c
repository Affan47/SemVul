ftt_cell_new (FttCellInitFunc init,
			gpointer data)
{
  FttCell * cell;

  cell = g_malloc0 (sizeof (FttRootCell));
  if (init)
    (* init) (cell, data);

  return cell;
}
