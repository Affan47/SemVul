zslDeleteRange(zskiplist *zsl, double min, double max, dict *dict) {
    zskiplistNode *update[ZSKIPLIST_MAXLEVEL], *x;
    unsigned long removed = 0;
    int i;

    x = zsl->header;
    for (i = zsl->level-1; i >= 0; i--) {
        while (x->forward[i] && x->forward[i]->score < min)
            x = x->forward[i];
        update[i] = x;
    }


    x = x->forward[0];
    while (x && x->score <= max) {
        zskiplistNode *next;

        for (i = 0; i < zsl->level; i++) {
            if (update[i]->forward[i] != x) break;
            update[i]->forward[i] = x->forward[i];
        }
        if (x->forward[0]) {
            x->forward[0]->backward = (x->backward == zsl->header) ?
                                        NULL : x->backward;
        } else {
            zsl->tail = x->backward;
        }
        next = x->forward[0];
        dictDelete(dict,x->obj);
        zslFreeNode(x);
        while(zsl->level > 1 && zsl->header->forward[zsl->level-1] == NULL)
            zsl->level--;
        zsl->length--;
        removed++;
        x = next;
    }
    return removed;
}
