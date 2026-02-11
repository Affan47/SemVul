clish_param_new(const char    *name,
                const char    *text,
                clish_ptype_t *ptype)
{
    clish_param_t *this = malloc(sizeof(clish_param_t));

    if(this)
    {
        clish_param_init(this,name,text,ptype);
    }
    return this;
}
