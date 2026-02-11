parse_include_list(char *list)
{
    struct include_field *ret = NULL,*c = NULL;
    char *p = list;
    char *w = list;
    char *s = list;

    if(p == NULL) return NULL;

    while(*p)
    {
        if(*p == ',' && p[1] == ',')
        {
            p++;
            *w = *p;
            w++;
            p++;
        }
        *w = *p;
        if(*p == ',' || !p[1])
        {
            if(p[1]) *w = 0;
            if(strlen(s))
            {
                if(ret == NULL)
                {
                    ret = xmalloc(sizeof(struct include_field));
                    c = ret;
                } else
                {
                    c->next = xmalloc(sizeof(struct include_field));
                    c = c->next;
                }
                c->next = NULL;
                c->name = xstrdup(s);
                c->found = 0;
                c->reported = 0;
            }
            p++;
            while(*p == ',') p++;
            s = p;
            w = s;
            p = s;
        } else
        {
            w++;
            p++;
        }
    }
    return ret;
}
