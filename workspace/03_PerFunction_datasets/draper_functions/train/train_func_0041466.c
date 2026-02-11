slotChildStarted( KIO::Job *job )
{
  khtml::ChildFrame *child = frame( sender() );

  assert( child );

  child->m_bCompleted = false;

  if ( d->m_bComplete )
  {
#if 0

    if ( !parentPart() )
    {
      emit d->m_extension->openURLNotify();
    }
#endif
    d->m_bComplete = false;
    emit started( job );
  }
}
