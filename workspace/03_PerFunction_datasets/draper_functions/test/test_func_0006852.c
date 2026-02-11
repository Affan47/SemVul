Exonerate_Server_set_param_max_target_span(
              Exonerate_Server_Connection *connection, GPtrArray *word_list){
    register gint max_target_span= atoi(word_list->pdata[3]);
    if(max_target_span < 0)
        return g_strdup_printf("error: max_target_span must be >= 0\n");
    connection->max_target_span = max_target_span;
    return g_strdup_printf("ok: set\n");
    }
