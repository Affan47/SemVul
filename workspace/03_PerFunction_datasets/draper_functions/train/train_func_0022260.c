actualMessage( const Message &message,
                          const ProtectorContext &context ) const
{
  Message theActualMessage;
  if ( context.m_shortDescription.empty() )
    theActualMessage = message;
  else
  {
    theActualMessage = Message( context.m_shortDescription,
                                message.shortDescription() );
    theActualMessage.addDetail( message );
  }

  return theActualMessage;
}
