gnc_owner_set_owner (GtkWidget *widget, GncOwner *owner)
{
    g_return_if_fail (widget != NULL);
    g_return_if_fail (owner != NULL);


    gnc_general_search_set_selected (GNC_GENERAL_SEARCH (widget),
                                     owner->owner.undefined);
}
