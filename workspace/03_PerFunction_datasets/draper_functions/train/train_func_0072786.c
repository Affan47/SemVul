keyboard_filter_event( const UniqueInputEvent *event,
                       const UniqueInputEvent *filter )
{
     D_ASSERT( event != NULL );
     D_ASSERT( filter != NULL );

     D_DEBUG_AT( UniQuE_Keyboard, "keyboard_filter_event( %p, %p )\n", event, filter );

     if (filter->keyboard.key_code != -1)
          return (filter->keyboard.key_code == event->keyboard.key_code);

     return (event->keyboard.modifiers  == filter->keyboard.modifiers &&
             event->keyboard.key_symbol == filter->keyboard.key_symbol);
}
