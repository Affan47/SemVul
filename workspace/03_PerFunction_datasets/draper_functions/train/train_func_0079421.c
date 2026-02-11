slotWriteActivity( int socket ) {


  const QDisabler<QSocketNotifier> disabled( qobject_cast<QSocketNotifier*>( sender() ) );
  actOn( socket , Write );
}
