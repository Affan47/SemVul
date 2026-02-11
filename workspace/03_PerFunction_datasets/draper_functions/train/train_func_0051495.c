sfvt_add_str(vartable_t *table, char *str, sfip_var_t **ipret)
{
    sfip_var_t *var;
    sfip_var_t *swp;
    sfip_var_t *p;
    int ret;
    SFIP_RET status;

    if(!table || !str || !ipret) return SFIP_FAILURE;


    if( (var = sfvar_alloc(table, str, &status)) == NULL )
    {
         return status;
    }


    if (var->id == 0)
        var->id = table->id++;

    *ipret = var;


    if(!table->head)
    {
        table->head = var;
        return SFIP_SUCCESS;
    }

    if((ret = strcmp(var->name, table->head->name)) < 0)
    {
        var->next = table->head;
        table->head = var;
        return SFIP_SUCCESS;
    }

    else if(ret == 0)
    {
        var->next = table->head->next;
        sfvar_free(table->head);
        table->head = var;
        return SFIP_DUPLICATE;
    }


    if(!table->head->next)
    {
        table->head->next = var;
        return SFIP_SUCCESS;
    }
    else if(!strcmp(var->name, table->head->next->name))
    {
        var->next = table->head->next->next;
        sfvar_free(table->head->next);
        table->head->next = var;
        return SFIP_DUPLICATE;
    }

    for(p = table->head; p->next; p=p->next)
    {
        if((ret = strcmp(var->name, p->next->name)) < 0)
        {
            swp = p->next;
            p->next = var;
            var->next = swp;

            return SFIP_SUCCESS;
        }

        else if(ret == 0)
        {
            var->next = p->next->next;
            sfvar_free(p->next);
            p->next = var;
            return SFIP_DUPLICATE;
        }
    }

    p->next = var;
    return SFIP_SUCCESS;
}
