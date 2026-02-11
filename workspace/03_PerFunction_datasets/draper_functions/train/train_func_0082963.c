dispatch_channel( UniqueWindow           *window,
                  const UniqueInputEvent *event )
{
     DFBWindowEvent evt;

     D_MAGIC_ASSERT( window, UniqueWindow );

     D_ASSERT( event != NULL );

     switch (event->channel.index) {
          case UDCI_POINTER:
               evt.type = event->channel.selected ? DWET_ENTER : DWET_LEAVE;
               break;

          case UDCI_KEYBOARD:
               evt.type = event->channel.selected ? DWET_GOTFOCUS : DWET_LOSTFOCUS;
               break;

          default:
               return;
     }

     evt.cx = event->channel.x;
     evt.cy = event->channel.y;
     evt.x  = event->channel.x - window->bounds.x;
     evt.y  = event->channel.y - window->bounds.y;

     dfb_window_post_event( window->window, &evt );
}
