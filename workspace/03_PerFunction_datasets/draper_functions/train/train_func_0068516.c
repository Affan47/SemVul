compare(struct element *a, struct element *b, int(*cmp)(const void*, const void *))
{
    int rc;

    rc = cmp(a->item, b->item);
    if (rc == 0) {

        if (a->seq < b->seq)
            rc = 1;
        else if (a->seq > b->seq)
            rc = -1;
    }

    return rc;
}
