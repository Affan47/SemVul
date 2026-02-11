handle_save_outgoings(struct ntb_store *store,
                      struct ntb_store_task *task)
{
        struct ntb_blob *blob = task->save_outgoings.blob;
        const struct ntb_store_outgoing *outgoings =
                (const struct ntb_store_outgoing *) blob->data;
        FILE *out;
        size_t i;

        ntb_log("Saving outgoing messages");

        store->filename_buf.length = store->directory_len;
        ntb_buffer_append_string(&store->filename_buf,
                                 "outgoing-messages.dat.tmp");

        out = fopen((char *) store->filename_buf.data, "w");

        if (out == NULL) {
                ntb_log("Error opening %s: %s",
                        (char *) store->filename_buf.data,
                        strerror(errno));
                return;
        }

        for (i = 0; i < blob->size / sizeof *outgoings; i++)
                write_outgoing(outgoings + i, out);

        if (fclose(out) == EOF) {
                ntb_log("Error writing to %s: %s",
                        (char *) store->filename_buf.data,
                        strerror(errno));
                return;
        }

        rename_tmp_file(store);
}
