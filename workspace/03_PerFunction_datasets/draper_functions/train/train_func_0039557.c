arm()
{
   Event* e = getTargetEventName();
   if ( e )
      e->executed.connect( SigC::slot( *this, &EventTriggered::triggered));
}
