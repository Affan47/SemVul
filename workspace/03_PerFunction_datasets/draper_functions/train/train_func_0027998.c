rngdic_destruct(RangeDic *dic)
{


    RangeDicItem *item;
    List *li;

    if (dic == NULL) {
        return;
    }

    for (li = dic->items; li != NULL; li = li->next) {
        item = li->data;
        if (item == NULL) {
            continue;
        }

        if (item->x != NULL) {
            semtree_destruct(item->x);
            item->x = NULL;
        }
        if (item->min != NULL) {
            semtree_destruct(item->min);
            item->min = NULL;
        }
        if (item->max != NULL) {
            semtree_destruct(item->max);
            item->max = NULL;
        }
    }

    list_free(dic->items);

    free(dic);
}
