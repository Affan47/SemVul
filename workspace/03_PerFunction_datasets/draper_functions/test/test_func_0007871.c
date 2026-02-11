ReceiveAIEvent(AIEventType eventType, Creature* pSender, Unit* pInvoker, uint32 )
{
    MANGOS_ASSERT(pSender);

    for (CreatureEventAIList::iterator itr = m_CreatureEventAIList.begin(); itr != m_CreatureEventAIList.end(); ++itr)
    {
        if (itr->Event.event_type == EVENT_T_RECEIVE_AI_EVENT &&
                itr->Event.receiveAIEvent.eventType == eventType && (!itr->Event.receiveAIEvent.senderEntry || itr->Event.receiveAIEvent.senderEntry == pSender->GetEntry()))
            ProcessEvent(*itr, pInvoker, pSender);
    }
}
