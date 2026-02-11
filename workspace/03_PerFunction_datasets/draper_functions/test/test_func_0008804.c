set_compare_event ( unsigned int value, CCPCON *host )
{
  TMR1CapComRef * event = compare_queue;

  if ( host )
  {
    while ( event )
    {
      if ( event->ccpcon == host )
      {
        event->value = value;
        update();
        return;
      }
      event = event->next;
    }
    event = new TMR1CapComRef ( host, value );
    event->next = compare_queue;
    compare_queue = event;
    update();
  }
  else
      cout << "TMRL::set_compare_event called with no CAPCOM\n";
}
