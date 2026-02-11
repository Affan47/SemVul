dico_destroy(cdico *d)
{
    cdicoitem *item, *next;

    if (d==NULL)
        return -1;

    item=d->head;
    while (item!=NULL)
    {
        next=item->next;
        if (item->data!=NULL)
            free(item->data);
        free(item);
        item=next;
    }

    free(d);

    return 0;
}
