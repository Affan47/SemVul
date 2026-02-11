sfvt_lookup_var(vartable_t *table, char *name)
{
    sfip_var_t *p;
    int len;
    char *end;

    if(!table || !name) return NULL;

    if(*name == '$') name++;


    for(end=name;
        *end && !isspace((int)*end) && *end != '\\' && *end != ']';
        end++) ;
    len = end - name;

    for(p=table->head; len && p; p=p->next)
    {
        int name_len = strlen(p->name);
        if((len == name_len) && !strncmp(p->name, name, len)) return p;
    }

    return NULL;
}
