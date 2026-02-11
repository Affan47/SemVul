gnc_reconcile_view_get_num_splits (GNCReconcileView *view)
{
    g_return_val_if_fail (view != NULL, 0);
    g_return_val_if_fail (GNC_IS_RECONCILE_VIEW (view), 0);

    return gnc_query_view_get_num_entries (GNC_QUERY_VIEW (view));
}
