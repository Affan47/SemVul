Cddb_Get_Album_Tracks_List_CB (GtkTreeSelection *selection, gpointer data)
{
    gint i;
    gint i_max = 5;


    for (i = 1; i <= i_max; i++)
    {
        if ( Cddb_Get_Album_Tracks_List(selection) == TRUE )
        {
            break;
        }
    }
    if (i <= i_max)
    {
        return TRUE;
    } else
    {
        return FALSE;
    }
}
