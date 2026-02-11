convert_clipboard_manager (GsdClipboardManager *manager,
                           XEvent              *xev)
{
        Atom          type = None;
        int           format;
        unsigned long nitems;
        unsigned long remaining;
        Atom         *targets = NULL;

        if (xev->xselectionrequest.target == XA_SAVE_TARGETS) {
                if (manager->priv->requestor != None || manager->priv->contents != NULL) {


                        finish_selection_request (manager, xev, False);
                } else {
                        gdk_error_trap_push ();

                        clipboard_manager_watch_cb (manager,
                                                    xev->xselectionrequest.requestor,
                                                    True,
                                                    StructureNotifyMask,
                                                    NULL);
                        XSelectInput (manager->priv->display,
                                      xev->xselectionrequest.requestor,
                                      StructureNotifyMask);
                        XSync (manager->priv->display, False);

                        if (gdk_error_trap_pop () != Success)
                                return;

                        gdk_error_trap_push ();

                        if (xev->xselectionrequest.property != None) {
                                XGetWindowProperty (manager->priv->display,
                                                    xev->xselectionrequest.requestor,
                                                    xev->xselectionrequest.property,
                                                    0, 0x1FFFFFFF, False, XA_ATOM,
                                                    &type, &format, &nitems, &remaining,
                                                    (unsigned char **) &targets);

                                if (gdk_error_trap_pop () != Success) {
                                        if (targets)
                                                XFree (targets);

                                        return;
                                }
                        }

                        manager->priv->requestor = xev->xselectionrequest.requestor;
                        manager->priv->property = xev->xselectionrequest.property;
                        manager->priv->time = xev->xselectionrequest.time;

                        if (type == None)
                                XConvertSelection (manager->priv->display, XA_CLIPBOARD,
                                                   XA_TARGETS, XA_TARGETS,
                                                   manager->priv->window, manager->priv->time);
                        else
                                save_targets (manager, targets, nitems);
                }
        } else if (xev->xselectionrequest.target == XA_TIMESTAMP) {
                XChangeProperty (manager->priv->display,
                                 xev->xselectionrequest.requestor,
                                 xev->xselectionrequest.property,
                                 XA_INTEGER, 32, PropModeReplace,
                                 (unsigned char *) &manager->priv->timestamp, 1);

                finish_selection_request (manager, xev, True);
        } else if (xev->xselectionrequest.target == XA_TARGETS) {
                int  n_targets = 0;
                Atom targets[3];

                targets[n_targets++] = XA_TARGETS;
                targets[n_targets++] = XA_TIMESTAMP;
                targets[n_targets++] = XA_SAVE_TARGETS;

                XChangeProperty (manager->priv->display,
                                 xev->xselectionrequest.requestor,
                                 xev->xselectionrequest.property,
                                 XA_ATOM, 32, PropModeReplace,
                                 (unsigned char *) targets, n_targets);

                finish_selection_request (manager, xev, True);
        } else
                finish_selection_request (manager, xev, False);
}
