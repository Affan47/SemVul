qof_collection_lookup_entity (const QofCollection *col, const GncGUID * guid)
{
    QofInstance *ent;
    g_return_val_if_fail (col, NULL);
    if (guid == NULL) return NULL;
    ent = g_hash_table_lookup (col->hash_of_entities, guid);
    return ent;
}
