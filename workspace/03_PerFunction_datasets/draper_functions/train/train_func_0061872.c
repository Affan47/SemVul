cli_print_volume_tasks (dict_t *dict) {
        int             ret = -1;
        int             tasks = 0;
        char            *op = 0;
        char            *task_id_str = NULL;
        int             status = 0;
        char            key[1024] = {0,};
        int             i = 0;

        ret = dict_get_int32 (dict, "tasks", &tasks);
        if (ret) {
                gf_log ("cli", GF_LOG_ERROR,
                        "Failed to get tasks count");
                return;
        }

        if (tasks == 0) {
                cli_out ("There are no active volume tasks");
                return;
        }

        cli_out ("%15s%40s%15s", "Task", "ID", "Status");
        cli_out ("%15s%40s%15s", "----", "--", "------");
        for (i = 0; i < tasks; i++) {
                memset (key, 0, sizeof (key));
                snprintf (key, sizeof (key), "task%d.type", i);
                ret = dict_get_str(dict, key, &op);
                if (ret)
                        return;

                memset (key, 0, sizeof (key));
                snprintf (key, sizeof (key), "task%d.id", i);
                ret = dict_get_str (dict, key, &task_id_str);
                if (ret)
                        return;

                memset (key, 0, sizeof (key));
                snprintf (key, sizeof (key), "task%d.status", i);
                ret = dict_get_int32 (dict, key, &status);
                if (ret)
                        return;


                if (!strcmp (op, "Replace brick")) {
                    if (status) {
                        status = GF_DEFRAG_STATUS_COMPLETE;
                    } else {
                        status = GF_DEFRAG_STATUS_STARTED;
                    }
                }

                cli_out ("%15s%40s%15s", op, task_id_str,
                         cli_vol_task_status_str[status]);
        }

}
