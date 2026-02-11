server_writeto_all_gui_clients(const void *data, size_t size) {
    client_t *client = guiclients;
    if (client) do {
        server_writeto(client, data, size);
        client = client->next_gui;
    } while (client != guiclients);
}
