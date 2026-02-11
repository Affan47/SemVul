gnc_combo_cell_new (void)
{
    ComboCell * cell;

    g_once(&auto_pop_init_once, gnc_combo_cell_autopop_init, NULL);

    cell = g_new0 (ComboCell, 1);

    gnc_combo_cell_init (cell);

    return &cell->cell;
}
