lircEventThread( DirectThread *thread, void *driver_data )
{
     int                      repeats = 0;
     DFBInputDeviceKeySymbol  last    = DIKS_NULL;
     LircData                *data    = (LircData*) driver_data;

     while (true) {
          struct timeval          tv;
          fd_set                  set;
          int                     result;
          int                     readlen;
          char                    buf[128];
          DFBInputEvent           evt;
          DFBInputDeviceKeySymbol symbol;

          FD_ZERO(&set);
          FD_SET(data->fd,&set);

          tv.tv_sec  = 0;
          tv.tv_usec = 200000;

          result = select (data->fd+1, &set, NULL, NULL, &tv);

          switch (result) {
               case -1:

                    if (errno == EINTR)
                         continue;

                    D_PERROR("DirectFB/LIRC: select() failed\n");
                    return NULL;

               case 0:

                    if (last != DIKS_NULL) {
                         evt.flags      = DIEF_KEYSYMBOL;
                         evt.type       = DIET_KEYRELEASE;
                         evt.key_symbol = last;

                         dfb_input_dispatch( data->device, &evt );

                         last = DIKS_NULL;
                    }
                    continue;

               default:

                    break;
          }

          direct_thread_testcancel( thread );


          readlen = read( data->fd, buf, 128 );
          if (readlen < 1)
               continue;


          symbol = lirc_parse_line( buf );
          if (symbol == DIKS_NULL)
               continue;


          if (symbol == last) {

               if (++repeats < 4)
                    continue;
          }
          else {

               repeats = 0;


               if (last != DIKS_NULL) {
                    evt.flags      = DIEF_KEYSYMBOL;
                    evt.type       = DIET_KEYRELEASE;
                    evt.key_symbol = last;

                    dfb_input_dispatch( data->device, &evt );
               }
          }


          evt.flags      = DIEF_KEYSYMBOL;
          evt.type       = DIET_KEYPRESS;
          evt.key_symbol = symbol;

          dfb_input_dispatch( data->device, &evt );


          last = symbol;
     }

     return NULL;
}
