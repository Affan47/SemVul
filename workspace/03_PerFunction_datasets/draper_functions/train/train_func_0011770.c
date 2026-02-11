admin_get_command(const char *command)
{
    if(!strcmp(command, FALLBACK_RAW_REQUEST))
        return COMMAND_RAW_FALLBACK;
    else if(!strcmp(command, FALLBACK_TRANSFORMED_REQUEST))
        return COMMAND_TRANSFORMED_FALLBACK;
    else if(!strcmp(command, METADATA_RAW_REQUEST))
        return COMMAND_RAW_METADATA_UPDATE;
    else if(!strcmp(command, METADATA_TRANSFORMED_REQUEST))
        return COMMAND_TRANSFORMED_METADATA_UPDATE;
    else if(!strcmp(command, SHOUTCAST_METADATA_REQUEST))
        return COMMAND_SHOUTCAST_METADATA_UPDATE;
    else if(!strcmp(command, LISTCLIENTS_RAW_REQUEST))
        return COMMAND_RAW_SHOW_LISTENERS;
    else if(!strcmp(command, LISTCLIENTS_TRANSFORMED_REQUEST))
        return COMMAND_TRANSFORMED_SHOW_LISTENERS;
    else if(!strcmp(command, STATS_RAW_REQUEST))
        return COMMAND_RAW_STATS;
    else if(!strcmp(command, STATS_TRANSFORMED_REQUEST))
        return COMMAND_TRANSFORMED_STATS;
    else if(!strcmp(command, "stats.xml"))
        return COMMAND_RAW_STATS;
    else if(!strcmp(command, LISTMOUNTS_RAW_REQUEST))
        return COMMAND_RAW_LIST_MOUNTS;
    else if(!strcmp(command, LISTMOUNTS_TRANSFORMED_REQUEST))
        return COMMAND_TRANSFORMED_LIST_MOUNTS;
    else if(!strcmp(command, STREAMLIST_RAW_REQUEST))
        return COMMAND_RAW_LISTSTREAM;
    else if(!strcmp(command, STREAMLIST_PLAINTEXT_REQUEST))
        return COMMAND_PLAINTEXT_LISTSTREAM;
    else if(!strcmp(command, MOVECLIENTS_RAW_REQUEST))
        return COMMAND_RAW_MOVE_CLIENTS;
    else if(!strcmp(command, MOVECLIENTS_TRANSFORMED_REQUEST))
        return COMMAND_TRANSFORMED_MOVE_CLIENTS;
    else if(!strcmp(command, KILLCLIENT_RAW_REQUEST))
        return COMMAND_RAW_KILL_CLIENT;
    else if(!strcmp(command, KILLCLIENT_TRANSFORMED_REQUEST))
        return COMMAND_TRANSFORMED_KILL_CLIENT;
    else if(!strcmp(command, KILLSOURCE_RAW_REQUEST))
        return COMMAND_RAW_KILL_SOURCE;
    else if(!strcmp(command, KILLSOURCE_TRANSFORMED_REQUEST))
        return COMMAND_TRANSFORMED_KILL_SOURCE;
    else if(!strcmp(command, MANAGEAUTH_RAW_REQUEST))
        return COMMAND_RAW_MANAGEAUTH;
    else if(!strcmp(command, MANAGEAUTH_TRANSFORMED_REQUEST))
        return COMMAND_TRANSFORMED_MANAGEAUTH;
    else if(!strcmp(command, UPDATEMETADATA_RAW_REQUEST))
        return COMMAND_RAW_UPDATEMETADATA;
    else if(!strcmp(command, UPDATEMETADATA_TRANSFORMED_REQUEST))
        return COMMAND_TRANSFORMED_UPDATEMETADATA;
    else if(!strcmp(command, BUILDM3U_RAW_REQUEST))
        return COMMAND_BUILDM3U;
    else if(!strcmp(command, DEFAULT_TRANSFORMED_REQUEST))
        return COMMAND_TRANSFORMED_STATS;
    else if(!strcmp(command, DEFAULT_RAW_REQUEST))
        return COMMAND_TRANSFORMED_STATS;
    else
        return COMMAND_ERROR;
}
