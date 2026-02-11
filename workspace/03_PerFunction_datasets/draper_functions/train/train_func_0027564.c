irmo_client_set_state(IrmoClient *client, IrmoClientState state)
{
        IrmoCallbackList *callback_list;

        if (client->state != state) {
                client->state = state;

                callback_list = &client->state_change_callbacks[state];

                irmo_client_callback_raise(callback_list, client);
        }
}
