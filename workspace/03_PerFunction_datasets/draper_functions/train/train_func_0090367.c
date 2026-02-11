homebank_pref_set_string(
	GKeyFile *key_file,
    const gchar *group_name,
    const gchar *key,
	gchar *string)
{

	DB( g_print(" - homebank_pref_set_string :: group='%s' key='%s' value='%s'\n", group_name, key, string) );

	if( string != NULL && *string != '\0')
		g_key_file_set_string  (key_file, group_name, key, string);
	else
		g_key_file_set_string  (key_file, group_name, key, "");

}
