globus_l_guc_glob_list_cb(
    const char *                         url,
    const globus_gass_copy_glob_stat_t * info_stat,
    void *                               user_arg)
{
    int                                 end_ndx;
    char *                              tmp_str;
    globus_l_guc_info_t *               guc_info;
    globus_url_t                        url_info;
    char                                end_ch = ' ';

    memset(&url_info, '\0', sizeof(globus_url_t));
    globus_url_parse(url, &url_info);
    guc_info = (globus_l_guc_info_t *) user_arg;
    if(info_stat->type == GLOBUS_GASS_COPY_GLOB_ENTRY_DIR &&
        guc_info->recurse)
    {
        globus_fifo_enqueue(&guc_info->expanded_url_list, strdup(url));
    }

    if(url_info.url_path == NULL)
    {
        printf("    %s\n", url);
        return;
    }
    else
    {
        end_ndx = strlen(url_info.url_path) - 1;
        if(url_info.url_path[end_ndx] == '/')
        {
            url_info.url_path[end_ndx] = '\0';
            end_ch = '/';
        }

        tmp_str = strrchr(url_info.url_path, '/');
        *tmp_str = '\0';
        tmp_str++;
        printf("    %s%c\n", tmp_str, end_ch);
    }
    globus_url_destroy(&url_info);
}
