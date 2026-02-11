backend_id_to_index (const gchar *id)
{
        gint i;

        if (id == NULL)
        {
                return 0;
        }

        for (i=0; styles[i].id != NULL; i++)
        {
                if (g_ascii_strcasecmp (id, backends[i].id) == 0)
                {
                        return i;
                }
        }

        g_message( "Unknown barcode id \"%s\"", id );
        return 0;
}
