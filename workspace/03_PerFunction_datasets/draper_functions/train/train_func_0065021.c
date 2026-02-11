ipc_binary_add_arg(
    ipc_binary_message_t *msg,
    guint16 arg_id,
    gsize size,
    gpointer data,
    gboolean take_memory)
{

    g_assert(msg != NULL);
    g_assert(data != NULL);
    g_assert(arg_id > 0 && arg_id < msg->cmd->n_args);
    g_assert(msg->cmd->arg_flags[arg_id] & IPC_BINARY_EXISTS);
    g_assert(msg->args[arg_id].data == NULL);

    if (size == 0 && msg->cmd->arg_flags[arg_id] & IPC_BINARY_STRING) {
	size = strlen((gchar *)data);
    }

    if (!take_memory) {
	data = g_memdup(data, size);
    }

    msg->args[arg_id].len = size;
    msg->args[arg_id].data = data;
}
