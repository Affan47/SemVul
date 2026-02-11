a2j_dbus_send_method_return(
  struct a2j_dbus_method_call * call)
{
  if (call->reply == NULL)
  {
    a2j_debug("send_method_return() called with a NULL message, trying to construct a void return...");

    call->reply = dbus_message_new_method_return(call->message);
    if (call->reply == NULL)
    {
      a2j_error("Failed to construct method return!");
      return;
    }
  }

  if (!dbus_connection_send(call->connection, call->reply, NULL))
  {
    a2j_error("Ran out of memory trying to queue method return");
  }

  dbus_connection_flush(call->connection);
  dbus_message_unref(call->reply);
  call->reply = NULL;
}
