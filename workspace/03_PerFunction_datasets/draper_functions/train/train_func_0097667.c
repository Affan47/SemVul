dup_db_args(kadm5_server_handle_t handle, char **db_args)
{
    int count  = 0;
    int ret = 0;

    for (count=0; db_args && db_args[count]; count++);
    if (count == 0) {
        handle->db_args = NULL;
        goto clean_n_exit;
    }

    handle->db_args = calloc(sizeof(char*), count+1);
    if (handle->db_args == NULL) {
        ret=ENOMEM;
        goto clean_n_exit;
    }

    for (count=0; db_args[count]; count++) {
        handle->db_args[count] = strdup(db_args[count]);
        if (handle->db_args[count] == NULL) {
            ret = ENOMEM;
            goto clean_n_exit;
        }
    }

clean_n_exit:
    if (ret && handle->db_args) {
        for (count=0; handle->db_args[count]; count++)
            free(handle->db_args[count]);

        free(handle->db_args), handle->db_args = NULL;
    }

    return ret;
}
