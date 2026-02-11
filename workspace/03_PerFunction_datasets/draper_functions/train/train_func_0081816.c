client_remove_destroy_notify(ObClientCallback func)
{
    GSList *it;

    for (it = client_destroy_notifies; it; it = g_slist_next(it)) {
        ClientCallback *d = it->data;
        if (d->func == func) {
            g_slice_free(ClientCallback, d);
            client_destroy_notifies =
                g_slist_delete_link(client_destroy_notifies, it);
            break;
        }
    }
}
