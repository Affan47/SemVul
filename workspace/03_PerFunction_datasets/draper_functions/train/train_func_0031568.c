irmo_server_object_changed(IrmoServer *server, IrmoObject *obj,
                                IrmoClassVar *var)
{
        IrmoHashTableIterator iter;
        IrmoClient *client;

        irmo_hash_table_iterate(server->clients, &iter);

        while (irmo_hash_table_iter_has_more(&iter)) {
                client = irmo_hash_table_iter_next(&iter);


                if (client->state != IRMO_CLIENT_CONNECTED
                 && client->state != IRMO_CLIENT_SYNCHRONIZED) {
                        continue;
                }


                irmo_client_sendq_add_change(client, obj, var);
        }
}
