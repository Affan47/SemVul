globus_l_debug_parse_level_names(
    char *                              my_names,
    char **                             my_levels)
{
    char *                              name;
    int                                 i;


    name = my_names + strspn(my_names, " \t\n");
    for(i = 0; i < 32; i++)
    {
        if(*name)
        {
            my_levels[i] = name;


            name += strcspn(name, " \t\n");

            if(*name)
            {
                *(name++) = 0;

                name += strspn(name, " \t\n");
            }
        }
        else
        {
            my_levels[i] = GLOBUS_NULL;
        }
    }
}
