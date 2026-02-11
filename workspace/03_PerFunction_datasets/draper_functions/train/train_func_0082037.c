agent_release(DBusConnection *connection,
		DBusMessage *message, void *user_data)
{
	g_dbus_unregister_interface(connection, agent_path(), AGENT_INTERFACE);
	agent_registered = false;

	pending_message_remove();
	pending_command_complete("Agent unregistered by ConnMan\n");

	if (__connmanctl_is_interactive() == false)
		__connmanctl_quit();

	return dbus_message_new_method_return(message);
}
