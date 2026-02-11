Analysis_Client_set_query(Analysis_Client *aclient, Sequence *seq){
    register gchar *seq_str = Sequence_get_str(seq);
    register gchar *msg = g_strdup_printf("set query %s", seq_str);
    register gchar *reply = Analysis_Client_send(aclient, msg, "ok:", FALSE);
    register gchar **word;
    register gint len, checksum;
    if(strncmp(reply, "ok:", 3))
        g_error("Could not set query [%s] on server", seq->id);
    word = g_strsplit(reply+4, " ", 4);
    len = atoi(word[0]);
    checksum = atoi(word[1]);
    if(seq->len != len)
        g_error("Query length mismatch on server %d %d", seq->len, len);
    if(Sequence_checksum(seq) != checksum)
        g_error("Query checksum mismatch on server %d %d",
                Sequence_checksum(seq), checksum);
    g_strfreev(word);
    g_free(reply);
    g_free(msg);
    g_free(seq_str);
    if(aclient->curr_query)
        Sequence_destroy(aclient->curr_query);
    aclient->curr_query = Sequence_share(seq);
    return;
    }
