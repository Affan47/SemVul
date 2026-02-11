flushQueue(RequestQueue &queue)
{


   RequestQueue::iterator wqit = m_waitQueue.begin();
   const RequestQueue::iterator wqend = m_waitQueue.end();
   while ( wqit != wqend )
   {
      const GetRequest& entry = *wqit;
      if ((m_url.protocol() == entry.url.protocol()) &&
          (m_url.host() == entry.url.host()) &&
          (m_url.port() == entry.url.port()) &&
          (m_url.user() == entry.url.user()))
      {
         queue.append( entry );
         wqit = m_waitQueue.erase( wqit );
      }
      else
      {
         ++wqit;
      }
   }

   KIO_ARGS << (qint32) queue.count();
   RequestQueue::const_iterator qit = queue.begin();
   const RequestQueue::const_iterator qend = queue.end();
   for( ; qit != qend; ++qit )
   {
      stream << (*qit).url << (*qit).metaData;
   }
   m_packedArgs = packedArgs;
   m_command = CMD_MULTI_GET;
   m_outgoingMetaData.clear();
}
