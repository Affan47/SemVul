sfipnode_alloc(char *str, SFIP_RET *status)
{
    sfip_node_t *ret;

    if(!str)
    {
        if(status)
            *status = SFIP_ARG_ERR;
        return NULL;
    }

    if( (ret = (sfip_node_t*)calloc(1, sizeof(sfip_node_t))) == NULL )
    {
        if(status)
            *status = SFIP_ALLOC_ERR;
         return NULL;
    }


    if(*str == '!')
    {
        str++;
        ret->flags |= SFIP_NEGATED;
    }


    if(!strncasecmp(str, "any", 3))
    {

        if(ret->flags & SFIP_NEGATED)
        {
            if(status)
                *status = SFIP_ARG_ERR;
            free(ret);
            return NULL;
        }

        ret->flags |= SFIP_ANY;

        if( (ret->ip = sfip_alloc("0.0.0.0", status)) == NULL )
        {

            if(status)
                *status = SFIP_ALLOC_ERR;

            free(ret);
            return NULL;
        }

        if(status)
            *status = SFIP_SUCCESS;

#if 0
        if( (ret->ip = sfip_alloc("0.0.0.0", NULL)) == NULL)
        {
            if(status)
                *status = SFIP_FAILURE;
            free(ret);
            return NULL;
        }
#endif

    }
    else if( (ret->ip = sfip_alloc(str, status)) == NULL )
    {

        if(status)
             *status = SFIP_INET_PARSE_ERR;
        free(ret);
        return NULL;
    }


    if(!sfip_is_set(ret->ip) && (ret->flags & SFIP_NEGATED))
    {
        if(status)
            *status = SFIP_NOT_ANY;
        free(ret->ip);
        free(ret);
        return NULL;
    }

    return ret;
}
