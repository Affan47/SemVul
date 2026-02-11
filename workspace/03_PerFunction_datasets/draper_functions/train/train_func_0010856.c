save_collection(FILE * file, gboolean * cancel)
{
    GList *list;
    serialization_data *work;
    gboolean ok = FALSE;

    list = get_list_head();
    work = g_new(serialization_data, 1);
    work->file = file;
    work->file_id = 0;
    work->count = get_list_length();
    work->cwd = g_get_current_dir();

    if (print_header(work) == FALSE)
        goto error;

    while (*cancel == FALSE && list != NULL) {
        gboolean file_ok = serialize_file(list->data, work);
        if (file_ok == FALSE)
            goto error;

        list = list->next;
    }

    if (*cancel || print_footer(work->file) == FALSE)
        goto error;

    ok = TRUE;
    goto ok;

  error:
    ok = FALSE;

  ok:
    g_free(work->cwd);
    g_free(work);

    return ok ? 0 : 1;
}
