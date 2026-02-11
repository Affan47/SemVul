fuse_graph_switch_task (void *data)
{
        fuse_graph_switch_args_t *args = NULL;

        args = data;
        if (args == NULL) {
                goto out;
        }


        fuse_handle_opened_fds (args->this, args->old_subvol, args->new_subvol);

        fuse_handle_blocked_locks (args->this, args->old_subvol,
                                   args->new_subvol);

out:
        return 0;
}
