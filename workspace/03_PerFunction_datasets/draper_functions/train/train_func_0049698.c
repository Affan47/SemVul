gsr2_update_summary_label (GtkWidget *label,
                          xaccGetBalanceFn getter,
                          Account *leader,
                          GNCPrintAmountInfo print_info,
                          gnc_commodity *cmdty,
                          gboolean reverse,
                          gboolean euroFlag)
{
    gnc_numeric amount;
    char string[256];

    if ( label == NULL )
        return;

    amount = (*getter)( leader );

    if ( reverse )
    {
        amount = gnc_numeric_neg( amount );
    }

    xaccSPrintAmount( string, amount, print_info );

    if ( euroFlag )
    {
        strcat( string, " / " );
        xaccSPrintAmount( string + strlen( string ),
                          gnc_convert_to_euro( cmdty, amount ),
                          gnc_commodity_print_info( gnc_get_euro(), TRUE ) );
    }

    gnc_set_label_color( label, amount );
    gtk_label_set_text( GTK_LABEL(label), string );
}
