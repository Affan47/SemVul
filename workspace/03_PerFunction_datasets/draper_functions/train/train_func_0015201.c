gifti_add_to_nvpairs(nvpairs * p, const char * name, const char * value)
{
    int index;

    if( !p || !name || !value ) {
        if(G.verb > 1) fprintf(stderr,"** GATN: bad params(%p,%p,%p)\n",
                               (void *)p, (void *)name, (void *)value);
        return 1;
    }

    p->length++;
    p->name = (char **)realloc(p->name, p->length * sizeof(char *));
    p->value = (char **)realloc(p->value, p->length * sizeof(char *));

    if( !p->name || !p->value ) {
        fprintf(stderr,"** GATN: failed to realloc %d pointers\n",p->length);
        return 1;
    } else if ( G.verb > 3 )
        fprintf(stderr,"++ add_nvp [%d]: '%s', '%s'\n", p->length,
                name ? name : "NULL", value ? value : "NULL");

    index = p->length - 1;
    p->name[index] = gifti_strdup(name);
    p->value[index] = gifti_strdup(value);

    if( !p->name[index] || !p->value[index] ) {
        fprintf(stderr,"** GATN: failed to copy pair '%s'='%s'\n",name,value);
        return 1;
    }

    return 0;
}
