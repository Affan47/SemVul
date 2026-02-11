Activate( void ) {
  if ( hook ) return hook->WidgetActivated( this, surface );
  return (GUI_Status)id;
}
