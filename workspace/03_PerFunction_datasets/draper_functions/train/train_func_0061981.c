systray_add(Window win)
{
     struct _systray *s;

     if(!(W->flags & WMFS_SYSTRAY))
          return;

     s = xcalloc(1, sizeof(struct _systray));
     s->win = win;

     s->geo.h = W->systray.barwin->geo.h;
     s->geo.w = W->systray.barwin->geo.h + SYSTRAY_SPACING;

     ewmh_set_wm_state(s->win, NormalState);
     XSelectInput(W->dpy, s->win, StructureNotifyMask | PropertyChangeMask| EnterWindowMask | FocusChangeMask);
     XReparentWindow(W->dpy, s->win, W->systray.win, 0, 0);

     ewmh_send_message(s->win, s->win, "_XEMBED", CurrentTime,
                       XEMBED_EMBEDDED_NOTIFY, 0, W->systray.win, 0);

     SLIST_INSERT_HEAD(&W->systray.head, s, next);

     W->systray.redim = true;
}
