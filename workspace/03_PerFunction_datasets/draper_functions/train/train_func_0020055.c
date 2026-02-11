gnc_price_cell_new (void)
{
    PriceCell *cell;

    cell = g_new0 (PriceCell, 1);

    gnc_price_cell_init (cell);

    return &cell->cell;
}
