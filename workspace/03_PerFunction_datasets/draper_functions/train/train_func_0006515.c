addStatistics( XmlElement *rootNode )
{
  XmlElement *statisticsElement = new XmlElement( "Statistics" );
  rootNode->addElement( statisticsElement );
  statisticsElement->addElement( new XmlElement( "Tests", m_result->runTests() ) );
  statisticsElement->addElement( new XmlElement( "FailuresTotal",
                                                 m_result->testFailuresTotal() ) );
  statisticsElement->addElement( new XmlElement( "Errors", m_result->testErrors() ) );
  statisticsElement->addElement( new XmlElement( "Failures", m_result->testFailures() ) );

  for ( Hooks::iterator it = m_hooks.begin(); it != m_hooks.end(); ++it )
    (*it)->statisticsAdded( m_xml, statisticsElement );
}
