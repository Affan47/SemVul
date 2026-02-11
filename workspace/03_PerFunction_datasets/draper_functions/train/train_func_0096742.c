WidgetActivated( Widget *widget, Window *win ) {

  switch( widget->ID() ) {
  case B_ID_EVENT:
    new ListSelectWindow( "Select event", tlist,
        event.GetData(0), false, this, B_ID_EVENT_OK, view );
    break;
  case B_ID_EVENT_OK: {
    TLWNode *n = static_cast<ListSelectWindow *>(win)->Selected();
    if ( n ) {
      Event *e = static_cast<Event *>( n->UserData() );
      if ( e->Trigger() != ETRIGGER_TIMER ) {
        n = NULL;
        new NoteWindow( "Error", "Selected event has no 'Timer' trigger.",
            0, view );
      }
    }
    event.SetData( 0, n ? n->ID() : -1 );
    e_event->SetString( n ? n->Name() : "Error" );
    break; }
  case B_ID_OFFSET:
    event.SetData( 2, static_cast<CycleWidget *>(widget)->GetValue() );
    break;
  case N_ID_TIME:
    event.SetData( 1, static_cast<NumberWidget *>(widget)->Number() );
    break;
  }

  return GUI_OK;
}
