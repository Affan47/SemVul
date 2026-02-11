gsb_file_open_direct_menu ( GtkMenuItem *item,
                        gint *file_number_ptr )
{

    if ( !gsb_file_close() )
	return FALSE;

    nom_fichier_comptes = my_strdup (tab_noms_derniers_fichiers_ouverts[GPOINTER_TO_INT (file_number_ptr)]);
    gsb_file_open_file (nom_fichier_comptes);

    return FALSE;
}
