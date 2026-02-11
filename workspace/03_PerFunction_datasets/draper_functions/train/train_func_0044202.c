PushToCecCommand(cec_command &command) const
{

  if (IsEmpty())
    return false;

  cec_adapter_messagecode msgCode = Message();
  if (msgCode == MSGCODE_FRAME_START)
  {
    command.Clear();
    if (Size() >= 3)
    {
      command.initiator   = Initiator();
      command.destination = Destination();
      command.ack         = IsACK();
      command.eom         = IsEOM();
    }
    return IsEOM() && !IsError();
  }
  else if (msgCode == MSGCODE_FRAME_DATA)
  {
    if (Size() >= 3)
    {
      command.PushBack(At(2));
      command.eom = IsEOM();
    }
    return IsEOM() && !IsError();
  }

  return false;
}
