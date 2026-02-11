_systray_handle_op_code(Instance *inst, Ecore_X_Event_Client_Message *ev)
{
   unsigned long message = ev->data.l[1];

   switch (message)
     {
      case SYSTEM_TRAY_REQUEST_DOCK:
        _systray_handle_request_dock(inst, ev);
        break;

      case SYSTEM_TRAY_BEGIN_MESSAGE:
      case SYSTEM_TRAY_CANCEL_MESSAGE:
        fputs("SYSTRAY TODO: handle messages (anyone uses this?)\n", stderr);
        break;

      default:
        fprintf(stderr,
                "SYSTRAY: error, unknown message op code: %ld, win: %#lx\n",
                message, ev->data.l[2]);
     }
}
