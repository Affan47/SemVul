seahorse_set_new (GQuark ktype, SeahorseUsage usage, SeahorseLocation location,
                     guint flags, guint nflags)
{
    SeahorseSet *skset;
    SeahorseObjectPredicate *pred = g_new0(SeahorseObjectPredicate, 1);

    pred->location = location;
    pred->id = ktype;
    pred->usage = usage;
    pred->flags = flags;
    pred->nflags = nflags;

    skset = seahorse_set_new_full (pred);
    g_object_set_data_full (G_OBJECT (skset), "quick-predicate", pred, g_free);

    return skset;
}
