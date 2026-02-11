sys_loglevel_option_handler (volgen_graph_t *graph,
                             struct volopt_map_entry *vme,
                             void *param)
{
        char  *role = NULL;
        struct volopt_map_entry vme2 = {0,};

        role = (char *) param;

        if (strcmp (vme->option, "!sys-log-level") != 0 ||
            !strstr (vme->key, role))
                return 0;

        memcpy (&vme2, vme, sizeof (vme2));
        vme2.option = "sys-log-level";

        return basic_option_handler (graph, &vme2, NULL);
}
