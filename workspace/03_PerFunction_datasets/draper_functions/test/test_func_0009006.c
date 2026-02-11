list_remove_entry(struct ucftpentry *ent)
{
    if(ent == NULL)
        return;

    if(ent->prevp != NULL)
        *ent->prevp = ent->next;
    if(ent->next != NULL)
        ent->next->prevp = ent->prevp;

    ent->prevp = NULL;
    ent->next = NULL;
}
