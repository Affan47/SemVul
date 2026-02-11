gncEntryCompare (const GncEntry *a, const GncEntry *b)
{
    int compare;

    if (a == b) return 0;
    if (!a && b) return -1;
    if (a && !b) return 1;

    compare = timespec_cmp (&(a->date), &(b->date));
    if (compare) return compare;

    compare = timespec_cmp (&(a->date_entered), &(b->date_entered));
    if (compare) return compare;

    compare = g_strcmp0 (a->desc, b->desc);
    if (compare) return compare;

    compare = g_strcmp0 (a->action, b->action);
    if (compare) return compare;

    return qof_instance_guid_compare(a, b);
}
