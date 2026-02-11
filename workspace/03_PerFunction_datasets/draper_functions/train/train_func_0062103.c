ErrorMessageToGAPString(
    const Char *        msg,
    Int                 arg1,
    Int                 arg2 )
{
  Char message[120];
  Obj Message;
  SPrTo(message, 120, msg, arg1, arg2);
  message[119] = '\0';
  C_NEW_STRING(Message, strlen(message), message);
  return Message;
}
