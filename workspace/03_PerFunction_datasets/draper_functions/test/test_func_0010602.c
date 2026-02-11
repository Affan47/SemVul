etat_affiche_affiche_total_general ( gsb_real total_general,
					  gint ligne )
{
    gchar * text;
    gint current_report_number;

    current_report_number = gsb_gui_navigation_get_current_report ();


    etat_affiche_attach_label ( NULL, TEXT_NORMAL, 1, nb_colonnes, ligne, ligne + 1, ALIGN_CENTER, 0 );
    ligne++;

    etat_affiche_attach_hsep ( 0, nb_colonnes, ligne, ligne + 1 );
    ligne++;

    if ( gsb_data_report_get_show_report_transaction_amount (current_report_number))
    {
        gchar* fmtstr;
	if ( nb_ope_general_etat <= 1 )
	    fmtstr = _("General total (%d transaction): ");
	else
	    fmtstr = _("General total (%d transactions): ");
	text = g_strdup_printf ( fmtstr, nb_ope_general_etat );
    }
    else
	text = g_strdup( _("General total: ") );

    etat_affiche_attach_label ( text, TEXT_NORMAL, 0, nb_colonnes - 1, ligne, ligne + 1, ALIGN_LEFT, 0 );
    g_free ( text );

    text = gsb_real_get_string_with_currency (total_general, devise_generale_etat, TRUE );
    etat_affiche_attach_label ( text, TEXT_NORMAL, nb_colonnes - 1, nb_colonnes, ligne, ligne + 1, ALIGN_RIGHT, 0 );
    g_free ( text );
    ligne++;

    etat_affiche_attach_hsep ( 0, nb_colonnes, ligne, ligne + 1 );
    ligne++;

    etat_affiche_attach_label ( NULL, TEXT_NORMAL, 1, nb_colonnes, ligne, ligne + 1, ALIGN_CENTER, 0 );
    ligne++;

    return ( ligne );
}
