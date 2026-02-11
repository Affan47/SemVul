SendCommand(cec_adapter_messagecode msgCode, CCECAdapterMessage &params, bool bIsRetry )
{
  if (!IsOpen() || !m_adapterMessageQueue)
    return NULL;


  CCECAdapterMessage *output = new CCECAdapterMessage;
  output->PushBack(MSGSTART);
  output->PushEscaped((uint8_t)msgCode);
  output->Append(params);
  output->PushBack(MSGEND);


  if (!m_adapterMessageQueue->Write(output))
  {

    if (output->state == ADAPTER_MESSAGE_STATE_ERROR)
      m_port->Close();
    return output;
  }
  else
  {
    if (!bIsRetry && output->Reply() == MSGCODE_COMMAND_REJECTED && msgCode != MSGCODE_SET_CONTROLLED &&
        msgCode != MSGCODE_GET_BUILDDATE )
    {


      LIB_CEC->AddLog(CEC_LOG_DEBUG, "setting controlled mode and retrying");
      delete output;
      if (SetControlledMode(true))
        return SendCommand(msgCode, params, true);
    }
  }

  return output;
}
