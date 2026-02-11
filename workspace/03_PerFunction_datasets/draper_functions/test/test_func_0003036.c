gupnp_dlna_fraction_range_new_take (GUPnPDLNAFraction *min,
                                    GUPnPDLNAFraction *max)
{
        GUPnPDLNAFractionRange *range;

        g_return_val_if_fail (min != NULL, NULL);
        g_return_val_if_fail (max != NULL, NULL);

        range = g_slice_new (GUPnPDLNAFractionRange);
        range->min = min;
        range->max = max;

        return range;
}
