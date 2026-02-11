gnc_plugin_page_owner_tree_filter_owners (GncOwner *owner,
        gpointer user_data)
{
    OwnerFilterDialog *fd = user_data;
    gnc_numeric total;

    ENTER("owner %p:%s", owner, gncOwnerGetName(owner));

    if (!fd->show_inactive && !gncOwnerGetActive (owner))
    {
        LEAVE(" hide: inactive");
        return FALSE;
    }

    if (!fd->show_zero_total)
    {


        total = gnc_numeric_zero();
        if (gnc_numeric_zero_p(total))
        {
            LEAVE(" hide: zero balance");
            return FALSE;
        }
    }

    return TRUE;
}
