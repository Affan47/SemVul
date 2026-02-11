Send_Packet( PKTS &pkt )
{
    mT_RelayListIt CurrentCrossfeed = m_CrossfeedList.begin();
    while (CurrentCrossfeed != m_CrossfeedList.end()) {
        int sent = m_DataSocket->sendto(pkt.bgn, pkt.cnt, 0, &CurrentCrossfeed->Address);
        if (SERROR(sent)) {
            PERROR("sendto crossfeed failed!");
            m_CrossFeedFailed++;
        } else {
            m_CrossFeedSent++;
        }
        CurrentCrossfeed++;
    }
}
