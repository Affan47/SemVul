MessageReceived(const CCECAdapterMessage &message)
{
  bool bHandled(false);

  if (IsResponse(message))
  {
    switch (message.Message())
    {
    case MSGCODE_COMMAND_ACCEPTED:
      bHandled = MessageReceivedCommandAccepted(message);
      break;
    case MSGCODE_TRANSMIT_SUCCEEDED:
      bHandled = MessageReceivedTransmitSucceeded(message);
      break;
    default:
      bHandled = MessageReceivedResponse(message);
      break;
    }
  }

  return bHandled;
}
