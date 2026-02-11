postnet_validate_data (const gchar *data)
{
        gchar *p;
        gint   i;

        if (!data)
        {
                return 0;
        }

        for ( p = (gchar *)data, i=0; *p != 0; p++ )
        {
                if (g_ascii_isdigit (*p))
                {
                        i++;
                }
                else if ( (*p != '-') && (*p != ' ') )
                {

                        return 0;
                }
        }

        return i;
}
