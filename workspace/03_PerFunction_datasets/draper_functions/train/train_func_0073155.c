gnc_split_register_save_price_cell (BasicCell * bcell,
                                    gpointer save_data,
                                    gpointer user_data)
{
    SRSaveData *sd = save_data;
    PriceCell *cell = (PriceCell *) bcell;
    gnc_numeric price;

    g_return_if_fail (gnc_basic_cell_has_name (bcell, PRIC_CELL));

    price = gnc_price_cell_get_value (cell);

    DEBUG ("PRIC");


    if (!sd->handled_dc)
        xaccSplitSetSharePrice (sd->split, price);

    sd->do_scrub = TRUE;
}
