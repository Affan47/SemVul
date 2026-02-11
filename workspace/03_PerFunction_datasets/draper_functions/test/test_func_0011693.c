check_compact_table (IBusEngineSimple              *simple,
                     const IBusComposeTableCompact *table,
                     gint                           n_compose)
{
    IBusEngineSimplePrivate *priv = simple->priv;

    gint row_stride;
    guint16 *seq_index;
    guint16 *seq;
    gint i;


    if (n_compose > table->max_seq_len)
        return FALSE;


    seq_index = bsearch (priv->compose_buffer,
                         table->data,
                         table->n_index_size,
                         sizeof (guint16) *  table->n_index_stride,
                         compare_seq_index);

    if (seq_index == NULL) {

        return FALSE;
    }

    if (n_compose == 1) {

        return TRUE;
    }


    seq = NULL;

    for (i = n_compose - 1; i < table->max_seq_len; i++) {
        row_stride = i + 1;

        if (seq_index[i + 1] - seq_index[i] > 0) {
            seq = bsearch (priv->compose_buffer + 1,
                           table->data + seq_index[i],
                           (seq_index[i + 1] - seq_index[i]) / row_stride,
                           sizeof (guint16) * row_stride,
                           compare_seq);


            if (seq) {
                if (i == n_compose - 1)
                    break;
                else {
                    ibus_engine_simple_update_preedit_text (simple);

                    return TRUE;
                }
            }
        }
    }

    if (!seq) {

        return FALSE;
    }
    else {
        gunichar value;

        value = seq[row_stride - 1];
        ibus_engine_simple_commit_char (simple, value);
        priv->compose_buffer[0] = 0;


        return TRUE;
    }
}
