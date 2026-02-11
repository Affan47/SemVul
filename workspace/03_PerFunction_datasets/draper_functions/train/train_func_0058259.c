csv_import_parse_value_date ( struct struct_ope_importation * ope, gchar * string )
{
    g_return_val_if_fail ( string, FALSE );

    if (ope -> date_de_valeur )
        g_free ( ope -> date_de_valeur);
    ope -> date_de_valeur = gsb_parse_date_string ( string );

    return g_date_valid ( ope -> date_de_valeur );
}
