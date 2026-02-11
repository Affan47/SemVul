rmvitem(cnddepRec  *root,
                          cnddepRec  *topprev,
                          cnddepRec  *prevtop,
                          cnddepRec  *prev,
                          cnddepRec  *item,
                          cnddepRec  **top)
{
    if (root==item) {
        root=item->next;
        if (root!=item->other) {
            item->next->other=item->other;
            root=item->next;
            *top=root;
        }
        else    *top=NULL;
    }
    else if (topprev && topprev->other==item) {
        topprev->other=item->next;
        prevtop->next=item->next;
        if (item->next && item->next->mtn==item->mtn) {
            *top=prevtop->next;
            (*top)->other=item->other;
        }
        else
            *top=NULL;
    }
    else    prev->next=item->next;

    disposecddep(item);
    return  root;
}
