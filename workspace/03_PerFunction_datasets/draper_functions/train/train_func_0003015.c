qif_massage_split(QifSplit split, QifContext ctx)
{
    const char *type = QIF_O_CATEGORY;
    char *name;

    if (split->cat.obj)
    {
        if (split->cat_is_acct)
        {
            type = QIF_O_ACCOUNT;
            name = split->cat.acct->name;
        }
        else
            name = split->cat.cat->name;

        split->cat.obj = qif_object_map_lookup(ctx, type, name);
    }

    if (split->cat_class)
    {
        split->cat_class = (QifClass) qif_object_map_lookup(ctx, QIF_O_CLASS,
                           split->cat_class->name);
    }
}
