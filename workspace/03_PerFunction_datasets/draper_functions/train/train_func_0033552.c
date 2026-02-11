symbol_to_id( DFBInputDeviceKeySymbol symbol )
{
     if (symbol >= 'a' && symbol <= 'z')
          return DIKI_A + symbol - 'a';

     if (symbol >= 'A' && symbol <= 'Z')
          return DIKI_A + symbol - 'A';

     if (symbol >= '0' && symbol <= '9')
          return DIKI_0 + symbol - '0';

     if (symbol >= DIKS_F1 && symbol <= DIKS_F12)
          return DIKI_F1 + symbol - DIKS_F1;

     switch (symbol) {
          case DIKS_ESCAPE:
               return DIKI_ESCAPE;

          case DIKS_CURSOR_LEFT:
               return DIKI_LEFT;

          case DIKS_CURSOR_RIGHT:
               return DIKI_RIGHT;

          case DIKS_CURSOR_UP:
               return DIKI_UP;

          case DIKS_CURSOR_DOWN:
               return DIKI_DOWN;

          case DIKS_ALTGR:
               return DIKI_ALT_R;

          case DIKS_CONTROL:
               return DIKI_CONTROL_L;

          case DIKS_SHIFT:
               return DIKI_SHIFT_L;

          case DIKS_ALT:
               return DIKI_ALT_L;

          case DIKS_META:
               return DIKI_META_L;

          case DIKS_SUPER:
               return DIKI_SUPER_L;

          case DIKS_HYPER:
               return DIKI_HYPER_L;

          case DIKS_TAB:
               return DIKI_TAB;

          case DIKS_ENTER:
               return DIKI_ENTER;

          case DIKS_SPACE:
               return DIKI_SPACE;

          case DIKS_BACKSPACE:
               return DIKI_BACKSPACE;

          case DIKS_INSERT:
               return DIKI_INSERT;

          case DIKS_DELETE:
               return DIKI_DELETE;

          case DIKS_HOME:
               return DIKI_HOME;

          case DIKS_END:
               return DIKI_END;

          case DIKS_PAGE_UP:
               return DIKI_PAGE_UP;

          case DIKS_PAGE_DOWN:
               return DIKI_PAGE_DOWN;

          case DIKS_CAPS_LOCK:
               return DIKI_CAPS_LOCK;

          case DIKS_NUM_LOCK:
               return DIKI_NUM_LOCK;

          case DIKS_SCROLL_LOCK:
               return DIKI_SCROLL_LOCK;

          case DIKS_PRINT:
               return DIKI_PRINT;

          case DIKS_PAUSE:
               return DIKI_PAUSE;

          case DIKS_BACKSLASH:
               return DIKI_BACKSLASH;

          case DIKS_PERIOD:
               return DIKI_PERIOD;

          case DIKS_COMMA:
               return DIKI_COMMA;

          default:
               ;
     }

     return DIKI_UNKNOWN;
}
