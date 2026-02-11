generic_gnc_commodity_lookup_after_child_handler(gpointer data_for_children,
        GSList* data_from_children,
        GSList* sibling_data,
        gpointer parent_data,
        gpointer global_data,
        gpointer *result,
        const gchar *tag,
        const gchar *child_tag,
        sixtp_child_result *child_result)
{
    CommodityLookupParseInfo *cpi =
        (CommodityLookupParseInfo *) data_for_children;

    g_return_val_if_fail(cpi, FALSE);
    g_return_val_if_fail(child_result, FALSE);
    if (child_result->type != SIXTP_CHILD_RESULT_NODE) return(FALSE);

    if (strcmp(child_result->tag, "space") == 0)
    {
        if (cpi->namespace) return(FALSE);
        cpi->namespace = (gchar *) child_result->data;
        child_result->should_cleanup = FALSE;
    }
    else if (strcmp(child_result->tag, "id") == 0)
    {
        if (cpi->id) return(FALSE);
        cpi->id = (gchar *) child_result->data;
        child_result->should_cleanup = FALSE;
    }
    else
    {

        return(FALSE);
    }

    return(TRUE);
}
