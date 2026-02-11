osinfo_filter_matches_default(OsinfoFilter *filter, OsinfoEntity *entity)
{
    g_return_val_if_fail(OSINFO_IS_FILTER(filter), FALSE);
    g_return_val_if_fail(OSINFO_IS_ENTITY(entity), FALSE);

    struct osinfo_filter_match_args args = { filter, entity, TRUE };
    g_hash_table_foreach(filter->priv->propertyConstraints,
                         osinfo_filter_match_iterator,
                         &args);

    return args.matched;
}
