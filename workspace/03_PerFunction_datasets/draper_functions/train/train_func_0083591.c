send_blocking(Message &msg, int timeout)
{
  DBusMessage *reply;
  InternalError e;

  if (this->_timeout != -1)
  {
    reply = dbus_connection_send_with_reply_and_block(_pvt->conn, msg._pvt->msg, this->_timeout, e);
  }
  else
  {
    reply = dbus_connection_send_with_reply_and_block(_pvt->conn, msg._pvt->msg, timeout, e);
  }

  if (e) throw Error(e);

  return Message(new Message::Private(reply), false);
}
