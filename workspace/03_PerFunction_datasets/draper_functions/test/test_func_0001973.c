globus_l_gram_usage_parse_target(
    char *                              target)
{
    char *                              ptr;
    globus_l_gram_usage_ent_t *         usage_ent;
    char *                              entry = NULL;
    char *                              conf_taglist = NULL;

    usage_ent = (globus_l_gram_usage_ent_t *)
        globus_malloc(sizeof(globus_l_gram_usage_ent_t));

    if(target && *target)
    {
        entry = globus_libc_strdup(target);
    }

    if(entry && (ptr = strchr(entry, '!')) != NULL)
    {
        *ptr = '\0';
        conf_taglist = ptr + 1;
    }

    if(conf_taglist == NULL ||
        strcasecmp(conf_taglist, "default") == 0)
    {
        usage_ent->job_taglist =
            globus_libc_strdup(GLOBUS_L_GRAM_DEFAULT_JOB_TAGLIST);
        usage_ent->session_taglist =
            globus_libc_strdup(GLOBUS_L_GRAM_DEFAULT_SESSION_TAGLIST);
    }
    else if(strcasecmp(conf_taglist, "all") == 0)
    {
        usage_ent->job_taglist = globus_libc_strdup(
            GLOBUS_L_GRAM_DEFAULT_JOB_TAGLIST
            GLOBUS_L_GRAM_PRIVATE_JOB_TAGLIST);
        usage_ent->session_taglist = globus_libc_strdup(
            GLOBUS_L_GRAM_DEFAULT_SESSION_TAGLIST
            GLOBUS_L_GRAM_PRIVATE_SESSION_TAGLIST);
    }
    else
    {
        usage_ent->job_taglist = globus_libc_strdup(conf_taglist);
        usage_ent->session_taglist = globus_libc_strdup(conf_taglist);
    }

    usage_ent->target = entry;

    globus_list_insert(&globus_l_gram_usage_handle_list, usage_ent);

    return;
}
