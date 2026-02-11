accept_listener_table_name(struct Listener *listener, char *table_name) {
    if (listener->table_name == NULL)
        listener->table_name = strdup(table_name);
    else
        fprintf(stderr, "Duplicate table_name: %s\n", table_name);

    return 1;
}
