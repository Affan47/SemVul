vt_is_used (gint number)
{
    GList *link;

    for (link = used_vts; link; link = link->next)
    {
        int n = GPOINTER_TO_INT (link->data);
        if (n == number)
            return TRUE;
    }

    return FALSE;
}
