gfork_l_list_to_array(
    globus_list_t *                     list)
{
    int                                 i = 0;
    char **                             argv;

    argv = (char **) calloc(
        globus_list_size(list) + 1, sizeof(char *));
    i = 0;
    for(list = list;
        !globus_list_empty(list);
        list = globus_list_rest(list))
    {
        argv[i] = (char *) globus_list_first(list);
        i++;
    }
    argv[i] = NULL;

    return argv;
}
