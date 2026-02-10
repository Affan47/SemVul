guc_l_pipe_to_stack_str(
    char *                              in_str)
{
    globus_list_t *                     list;
    globus_list_t *                     r_list = NULL;
    char *                              pipe_str;
    char *                              del_choices = "#$^*!|%&()'{}";
    char *                              del;
    char *                              word;
    char *                              tmp_s;
    globus_bool_t                       found;

    del = del_choices;
    found = GLOBUS_FALSE;
    while(!found)
    {
        if(strchr(in_str, *del) == NULL)
        {
            found = GLOBUS_TRUE;
        }
        else
        {
            del++;
            if(del == '\0')
            {
                fprintf(stderr, "The pipe string most contain at least one of the following characters: %s", del_choices);
                return NULL;
            }
        }
    }
    list = globus_list_from_string(in_str, ' ', " \t\r\n");


    while(!globus_list_empty(list))
    {
        word = (char *) globus_list_remove(&list, list);
        if(*word != '\0')
        {
            globus_list_insert(&r_list, word);
        }
    }

    if(globus_list_size(r_list) <= 0)
    {
        return NULL;
    }

    pipe_str = globus_common_create_string("popen:argv=");
    while(!globus_list_empty(r_list))
    {
        word = (char *) globus_list_remove(&r_list, r_list);
        tmp_s = globus_common_create_string("%s%c%s", pipe_str, *del, word);
        free(pipe_str);
        pipe_str = tmp_s;
    }
    return pipe_str;
}
