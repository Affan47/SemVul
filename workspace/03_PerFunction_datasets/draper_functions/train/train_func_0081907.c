find_the_actions(void)
{   int i; int32 j;
    char action_sub[MAX_IDENTIFIER_LENGTH+4];

    if (module_switch)
        for (i=0; i<no_actions; i++) action_byte_offset[i] = 0;
    else
    for (i=0; i<no_actions; i++)
    {   strcpy(action_sub, (char *) symbs[action_symbol[i]]);
        strcpy(action_sub + strlen(action_sub) - 3, "Sub");
        j = symbol_index(action_sub, -1);
        if (sflags[j] & UNKNOWN_SFLAG)
            error_named("There is no action routine called", action_sub);
        else
        if (stypes[j] != ROUTINE_T)
            error_named("Not an action routine:", action_sub);
        else
        {   action_byte_offset[i] = svals[j];
            sflags[j] |= USED_SFLAG;
        }
    }
}
