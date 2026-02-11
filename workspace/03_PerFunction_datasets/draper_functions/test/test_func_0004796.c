search_output(char *name)
{
    struct output *o = output;

    if(strcmp(name,"no") == 0) return no_output;
    if(strcmp(name,"raw") == 0) return raw;

    while(o != NULL)
    {
        if(strcmp(name,o->name) == 0) return o;
        o = o->next;
    }
    fprintf(stderr,"%s: Unknown output \'%s\'\n",program,name);
    return NULL;
}
