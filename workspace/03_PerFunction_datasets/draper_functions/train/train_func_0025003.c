addCb(char *id)
{
    logger(L_DBG, "addCb()");
    if (id == NULL) {
        return NULL;
    }

    type_cb *tmp = (type_cb *) calloc(sizeof(type_cb),1);
    tmp->id      = strdup(id);


    if (callbacks == NULL) {
        tmp->next = NULL;
    } else {
        tmp->next = callbacks;
    }
    callbacks = tmp;

    return tmp->id;
}
