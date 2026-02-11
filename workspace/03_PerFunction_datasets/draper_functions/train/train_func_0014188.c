free_bus_state(Bus_state bus_state)
{
    List *li;
    int i;

    if (bus_state == NULL)
        return ;
    for (i = 0; i < bus_number; i++) {
        for (li = bus_state[i]; li != NULL; li = li->next) {
            free_data_trans_group(li->data);
        }
        list_free(bus_state[i]);
    }
    free(bus_state);
}
