run( std::string testName,
                       bool doWait,
                       bool doPrintResult,
                       bool doPrintProgress )
{
  TextTestProgressListener progress;
  if ( doPrintProgress )
    m_eventManager->addListener( &progress );

  TestRunner *pThis = this;
  pThis->run( *m_eventManager, testName );

  if ( doPrintProgress )
    m_eventManager->removeListener( &progress );

  printResult( doPrintResult );
  wait( doWait );

  return m_result->wasSuccessful();
}
