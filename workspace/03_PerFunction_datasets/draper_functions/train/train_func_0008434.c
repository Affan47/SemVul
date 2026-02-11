bet_historical_get_type_transaction ( const GDate *date,
                        GDate *start_current_fyear,
                        GDate *date_max )
{
    gint result = -1;

    if ( g_date_compare ( date, date_max ) <= 0 )
    {
        if ( g_date_compare ( date, start_current_fyear ) >= 0 )
            result = 2;
        else
            result = 0;
    }
    else
    {
        if ( g_date_compare ( date, start_current_fyear ) >= 0 )
            result = 1;
    }

    return result;
}
