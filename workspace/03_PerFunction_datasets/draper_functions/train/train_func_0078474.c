gnc_price_cell_set_value (PriceCell * cell, gnc_numeric amount)
{
    const char *buff;

    if (cell == NULL)
        return FALSE;

    if (cell->fraction > 0)
        amount = gnc_numeric_convert (amount, cell->fraction, GNC_HOW_RND_ROUND_HALF_UP);

    cell->amount = amount;
    buff = gnc_price_cell_print_value (cell);
    cell->need_to_parse = FALSE;

    if (g_strcmp0 (buff, cell->cell.value) == 0)
        return FALSE;

    gnc_basic_cell_set_value_internal (&cell->cell, buff);

    return TRUE;
}
