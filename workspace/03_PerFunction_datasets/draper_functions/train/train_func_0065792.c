construct_local_path (const char   *requested_path,
                      const char   *user_agent,
                      HostPathData *host_path_data)
{
        GString *str;
        char *local_path;
        int len;

        local_path = NULL;

        if (user_agent != NULL) {
                GList *node;

                for (node = host_path_data->user_agents;
                     node;
                     node = node->next) {
                        UserAgent *agent;

                        agent = node->data;

                        if (g_regex_match (agent->regex,
                                           user_agent,
                                           0,
                                           NULL)) {
                                local_path = agent->local_path;
                        }
                }
        }

        if (local_path == NULL)
                local_path = host_path_data->local_path;

        if (!requested_path || *requested_path == 0)
                return g_strdup (local_path);

        if (*requested_path != '/')
                return NULL;

        str = g_string_new (local_path);


        requested_path += strlen (host_path_data->server_path);


        len = strlen (requested_path);
        while (requested_path[len - 1] == '/')
                len--;

        g_string_append_len (str,
                             requested_path,
                             len);

        return g_string_free (str, FALSE);
}
