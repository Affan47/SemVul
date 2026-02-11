canon_source_type(const char *name, const canon_cap_t * caps)
{
    if(name){
        int i;
        for(i=0; i<caps->slotlist->count; i++){
            if( !strcmp(name,caps->slotlist->slots[i].name))
                 return &(caps->slotlist->slots[i]);
        }
    }
    return &(caps->slotlist->slots[0]);
}
