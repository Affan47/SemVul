CheckTimedOutMessages(void)
{
  CLockObject lock(m_mutex);
  vector<uint64_t> timedOut;
  for (map<uint64_t, CCECAdapterMessageQueueEntry *>::iterator it = m_messages.begin(); it != m_messages.end(); it++)
  {
    if (it->second->TimedOutOrSucceeded())
    {
      timedOut.push_back(it->first);
      if (!it->second->m_bSucceeded)
        m_com->m_callback->GetLib()->AddLog(CEC_LOG_DEBUG, "command '%s' was not acked by the controller", CCECAdapterMessage::ToString(it->second->m_message->Message()));
      delete it->second->m_message;
      delete it->second;
    }
  }

  for (vector<uint64_t>::iterator it = timedOut.begin(); it != timedOut.end(); it++)
  {
    uint64_t iEntryId = *it;
    m_messages.erase(iEntryId);
  }
}
