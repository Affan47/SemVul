remplissage_liste_exo_etats ( void )
{
    GSList *list_tmp;

    if ( !liste_exo_etat )
	return;

    gtk_clist_clear ( GTK_CLIST ( liste_exo_etat ) );

    list_tmp = gsb_data_fyear_get_fyears_list ();

    while ( list_tmp )
    {
	gint fyear_number;
	gchar *name[1];
	gint row;

	fyear_number = gsb_data_fyear_get_no_fyear (list_tmp -> data);

	name[0] = my_strdup (gsb_data_fyear_get_name (fyear_number));


	row = gtk_clist_append ( GTK_CLIST ( liste_exo_etat ),
				   name );
	gtk_clist_set_row_data ( GTK_CLIST ( liste_exo_etat ),
				 row,
				 GINT_TO_POINTER (fyear_number));

	list_tmp = list_tmp -> next;
    }
}
