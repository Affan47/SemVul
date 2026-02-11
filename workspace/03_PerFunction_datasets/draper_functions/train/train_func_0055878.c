NeedsRetry(void) const
{
  return Reply() == MSGCODE_NOTHING ||
         Reply() == MSGCODE_RECEIVE_FAILED ||
         Reply() == MSGCODE_TIMEOUT_ERROR ||
         Reply() == MSGCODE_TRANSMIT_FAILED_LINE ||
         Reply() == MSGCODE_TRANSMIT_FAILED_TIMEOUT_DATA ||
         Reply() == MSGCODE_TRANSMIT_FAILED_TIMEOUT_LINE ||
         Reply() == MSGCODE_TRANSMIT_LINE_TIMEOUT;
}
