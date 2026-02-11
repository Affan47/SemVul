gsb_scheduler_list_set_largeur_col ( void )
{
    gint i;
    gint width;

    for ( i = 0 ; i < SCHEDULER_COL_VISIBLE_COLUMNS ; i++ )
    {
        width = ( scheduler_col_width[i] * ( scheduler_current_tree_view_width ) ) / 100;
        if ( width > 0 )
            gtk_tree_view_column_set_fixed_width ( scheduler_list_column[i], width );
    }

    return FALSE;
}
