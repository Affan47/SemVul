FcParsePriority (FcConfigParse *parse)
{
    FcVStack *v;
    FcObject *priority_order;
    int n;
    int i;

    n = FcVStackElements (parse);
    priority_order = (FcObject *) malloc (n * sizeof (FcObject *));
    if (priority_order == NULL) {
		FcConfigMessage (parse, FcSevereError, "out of memory");
    } else {
        i = 0;
        while (i < n) {
            v = FcVStackFetch (parse, n - i - 1);
            if (v->tag != FcVStackField) {
                FcConfigMessage (parse, FcSevereError, "not a property name");
                n = 0;
            } else {
                priority_order[i] = FcObjectFromName ((const char *) v->u.string);
                i++;
            }
        }
        FcInitPriorities (parse->config, priority_order, n);
        free (priority_order);
    }
    FcVStackClear (parse);
}
