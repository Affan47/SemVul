init_maildir(struct ntb_store *store,
             const char *maildir,
             struct ntb_error **error)
{
        const char *home;

        if (maildir) {
                append_absolute_path(&store->maildir_buf, maildir);
                ntb_buffer_append_c(&store->maildir_buf, '/');
        } else if ((home = getenv("HOME"))) {
                if (home[0] != '/') {
                        ntb_set_error(error,
                                      &ntb_store_error,
                                      NTB_STORE_ERROR_INVALID_MAILDIR,
                                      "The HOME path is not "
                                      "absolute");
                        return false;
                }

                ntb_buffer_append_string(&store->maildir_buf,
                                         home);
                strip_trailing_slashes(&store->maildir_buf);
                ntb_buffer_append_string(&store->maildir_buf,
                                         "/.maildir/");
        } else {
                ntb_set_error(error,
                              &ntb_store_error,
                              NTB_STORE_ERROR_INVALID_MAILDIR,
                              "HOME is not set");
                return false;
        }

        store->maildir_len = store->maildir_buf.length;

        ntb_buffer_append_string(&store->maildir_buf, "new");

        if (!ntb_mkdir_hierarchy(&store->maildir_buf, error))
                return false;

        ntb_buffer_set_length(&store->maildir_buf,
                              store->maildir_buf.length - 3);
        ntb_buffer_append_string(&store->maildir_buf, "tmp");

        if (!ntb_mkdir((const char *) store->maildir_buf.data, error))
                return false;

        ntb_buffer_set_length(&store->maildir_buf,
                              store->maildir_buf.length - 3);
        ntb_buffer_append_string(&store->maildir_buf, "cur");

        if (!ntb_mkdir((const char *) store->maildir_buf.data, error))
                return false;

        return true;
}
