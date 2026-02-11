owner_type_handler (xmlNodePtr node, gpointer owner_pdata)
{
    struct owner_pdata *pdata = owner_pdata;
    char* txt = dom_tree_to_text(node);
    g_return_val_if_fail(txt, FALSE);

    if (!g_strcmp0 (txt, GNC_ID_CUSTOMER))
        gncOwnerInitCustomer (pdata->owner, NULL);
    else if (!g_strcmp0 (txt, GNC_ID_JOB))
        gncOwnerInitJob (pdata->owner, NULL);
    else if (!g_strcmp0 (txt, GNC_ID_VENDOR))
        gncOwnerInitVendor (pdata->owner, NULL);
    else if (!g_strcmp0 (txt, GNC_ID_EMPLOYEE))
        gncOwnerInitEmployee (pdata->owner, NULL);
    else
    {
        PWARN ("Unknown owner type: %s", txt);
        g_free(txt);
        return FALSE;
    }

    g_free(txt);
    return TRUE;
}
