steal_reply()
{
  DBusMessage *dmsg = dbus_pending_call_steal_reply(_pvt->call);
  if (!dmsg)
  {
    dbus_bool_t callComplete = dbus_pending_call_get_completed(_pvt->call);

    if (callComplete)
      throw ErrorNoReply("No reply available");
    else
      throw ErrorNoReply("Call not complete");
  }

  return Message(new Message::Private(dmsg));
}
