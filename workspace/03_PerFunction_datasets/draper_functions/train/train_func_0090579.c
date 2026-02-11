item_intersect(RangeDicItem *i, const SemTree *new_min, const SemTree *new_max)
{
    if (new_min != NULL) {
        if (i->min == NULL) {
            i->min = semtree_dup(new_min);
        } else {
            semtree_destruct(i->min);
            i->min = NULL;
        }
    }

    if (new_max != NULL) {
        if (i->max == NULL) {
            i->max = semtree_dup(new_max);
        } else {
            semtree_destruct(i->max);
            i->max = NULL;
        }
    }
}
