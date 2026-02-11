Write(const cec_command &data, bool &bRetry, uint8_t iLineTimeout, bool bIsReply)
{
  cec_adapter_message_state retVal(ADAPTER_MESSAGE_STATE_UNKNOWN);
  if (!IsRunning())
    return retVal;

  CCECAdapterMessage *output = new CCECAdapterMessage(data, iLineTimeout);
  output->bFireAndForget = bIsReply;


  MarkAsWaiting(data.destination);


  if (bIsReply)
  {
    retVal = m_adapterMessageQueue->Write(output) ?
        ADAPTER_MESSAGE_STATE_WAITING_TO_BE_SENT : ADAPTER_MESSAGE_STATE_ERROR;
  }
  else
  {
    bRetry = (!m_adapterMessageQueue->Write(output) || output->NeedsRetry()) && output->transmit_timeout > 0;
    if (bRetry)
      Sleep(CEC_DEFAULT_TRANSMIT_RETRY_WAIT);
    retVal = output->state;

    delete output;
  }
  return retVal;
}
