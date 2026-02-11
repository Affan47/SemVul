argument_register(struct argument * argument, char * key,
                       char * description, unsigned char has_value) {

    struct argument_list * list = malloc(sizeof(struct argument_list));
    list->next = NULL;
    list->key = strdup(key);
    list->description = strdup(description);
    list->has_value = has_value;
    list->value = NULL;
    list->specified = 0;

    if (argument->list) {

        struct argument_list * list_ptr = argument->list;
        while (list_ptr->next) list_ptr = list_ptr->next;
        list_ptr->next = list;
        list->first = list_ptr->first;
    } else {
        list->first = list;
        argument->list = list;
    }

}
