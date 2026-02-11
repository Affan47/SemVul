filter_sound_event(SoundEventData *d) {
        GList *i, *n;

        do {

                for (i = sound_event_queue.head; i; i = n) {
                        SoundEventData *j;

                        j = i->data;
                        n = i->next;

                        if (d->object == j->object) {


                                if (d->signal_id == signal_id_widget_show &&
                                    j->signal_id == signal_id_widget_hide) {

                                        free_sound_event(d);
                                        free_sound_event(j);
                                        g_queue_delete_link(&sound_event_queue, i);

                                        return NULL;
                                }


                                if ((d->signal_id == signal_id_widget_hide &&
                                     j->signal_id == signal_id_dialog_response) ||

                                    (d->signal_id == signal_id_widget_window_state_event &&
                                     j->signal_id == signal_id_widget_hide) ||

                                    (d->signal_id == signal_id_widget_window_state_event &&
                                     j->signal_id == signal_id_widget_show)) {

                                        free_sound_event(d);
                                        d = j;
                                        g_queue_delete_link(&sound_event_queue, i);
                                        break;
                                }

                                if ((d->signal_id == signal_id_dialog_response &&
                                     j->signal_id == signal_id_widget_hide) ||

                                    (d->signal_id == signal_id_widget_show &&
                                     j->signal_id == signal_id_widget_window_state_event) ||

                                    (d->signal_id == signal_id_widget_hide &&
                                     j->signal_id == signal_id_widget_window_state_event) ||

                                    (d->signal_id == j->signal_id)) {

                                        free_sound_event(j);
                                        g_queue_delete_link(&sound_event_queue, i);
                                }

                        } else if (GTK_IS_WINDOW(d->object) && GTK_IS_WINDOW(j->object)) {

                                GdkWindowTypeHint dhint, jhint;

                                dhint = gtk_window_get_type_hint(GTK_WINDOW(d->object));
                                jhint = gtk_window_get_type_hint(GTK_WINDOW(j->object));

                                if (is_menu_hint(dhint) && is_menu_hint(jhint)) {

                                        if (d->signal_id == signal_id_widget_hide &&
                                            j->signal_id == signal_id_widget_show) {
                                                free_sound_event(d);
                                                d = j;
                                                g_queue_delete_link(&sound_event_queue, i);
                                                break;
                                        }

                                        if (d->signal_id == signal_id_widget_show &&
                                            j->signal_id == signal_id_widget_hide) {

                                                free_sound_event(j);
                                                g_queue_delete_link(&sound_event_queue, i);
                                        }
                                }
                        }
                }


        } while (i);


        return d;
}
