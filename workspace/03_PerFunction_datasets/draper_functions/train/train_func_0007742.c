pe_ipc_dispatch(const char *buffer, ssize_t length, gpointer userdata)
{
    xmlNode *msg = string2xml(buffer);

    if (msg) {
        route_message(C_IPC_MESSAGE, msg);
    }

    free_xml(msg);
    return 0;
}
