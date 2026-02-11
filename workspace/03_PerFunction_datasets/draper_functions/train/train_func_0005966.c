dom_tree_to_boolean(xmlNodePtr node, gboolean* b)
{
    gchar* text;

    text = dom_tree_to_text(node);
    if (g_ascii_strncasecmp(text, "true", 4) == 0)
    {
        *b = TRUE;
        return TRUE;
    }
    else if (g_ascii_strncasecmp(text, "false", 5) == 0)
    {
        *b = FALSE;
        return TRUE;
    }
    else
    {
        *b = FALSE;
        return FALSE;
    }
}
