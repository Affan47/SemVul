irmo_client_watch_state(IrmoClient *client,
                                      IrmoClientState state,
                                      IrmoClientCallback func,
                                      void *user_data)
{
        IrmoCallbackList *list;

	irmo_return_val_if_fail(client != NULL, NULL);
        irmo_return_val_if_fail(state >= 0, NULL);
        irmo_return_val_if_fail(state < IRMO_CLIENT_NUM_STATES, NULL);
	irmo_return_val_if_fail(func != NULL, NULL);

        list = &client->state_change_callbacks[state];

	return irmo_callback_list_add(list, func, user_data);
}
