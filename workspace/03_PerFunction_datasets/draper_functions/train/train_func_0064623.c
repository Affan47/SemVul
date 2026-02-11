timer_notify()
{
    guint timeleft;
    time_t t = time(0);
    struct tm *tm_time = localtime(&t);
    static guint min = -1;
    gchar message[100];
    gint i;

    if(min == -1)
        min = tm_time->tm_min;

    if(values.time_choice == TIME_CHOICE_TIME_FROM_NOW) {

        if(min != tm_time->tm_min) {
            min = tm_time->tm_min;

            if(values.time_from_now.min)
                values.time_from_now.min--;
            else {
                values.time_from_now.min = 59;
                values.time_from_now.hour--;
            }
        }
    }

    timeleft = time_left();

    if(action_get_type(values.current_action) == ACTION_TYPE_SHUTDOWN)
        sprintf(message, _("The computer will be shut down in :"));
    else if(action_get_type(values.current_action) == ACTION_TYPE_RESTART)
        sprintf(message, _("The computer will be restarted in :"));
    else if(action_get_type(values.current_action) == ACTION_TYPE_LOGOUT)
        sprintf(message, _("Time before logout :"));
    else
        sprintf(message, _("Time before action :"));

    if(timeleft >= SECS_IN_MIN) {
        int tvalue;

        if(timeleft < SECS_IN_HOUR) {

            tvalue = timeleft / SECS_IN_MIN;
            sprintf(message, N_("%s %u minute", "%s %u minutes", tvalue),
                    message, tvalue);


            if(timeleft < 5 * SECS_IN_MIN) {
                tvalue = timeleft % SECS_IN_MIN;
                sprintf(message, N_("%s and %u second", "%s and %u seconds", tvalue),
                        message, tvalue);
            }
        } else if(timeleft < SECS_IN_DAY) {
            tvalue = timeleft / SECS_IN_HOUR;
            sprintf(message, N_("%s %u hour", "%s %u hours", tvalue),
                    message, tvalue);

            tvalue = (timeleft % SECS_IN_HOUR) / SECS_IN_MIN;
            sprintf(message, N_("%s and %u minute", "%s and %u minutes", tvalue),
                    message, tvalue);
        } else {
            tvalue = timeleft / SECS_IN_DAY;
            sprintf(message, N_("%s %u day", "%s %u days", tvalue),
                    message, tvalue);

            tvalue = (timeleft % SECS_IN_DAY) / SECS_IN_HOUR;
            sprintf(message, N_("%s and %u hour", "%s and %u hours", tvalue),
                    message, tvalue);
        }

        gtk_tooltips_set_tip(tray_tooltips, tray_eventbox, message, NULL);

        for(i = 0; i < *values.time_when_notify.nb; i++) {
            if(timeleft == values.time_when_notify.time[i]) {
                gui_notification(message, NOTIFICATION_TYPE_IMPORTANT,
                                 NOTIFICATION_ICON_TIME);
            }
        }
    }
    else {
        sprintf(message, N_("%s %u second", "%s %u seconds", timeleft),
                message, timeleft);

        gtk_tooltips_set_tip(tray_tooltips, tray_eventbox, message, NULL);

        if(timeleft <= 30 && progress_confirm_open == FALSE)
            progress_confirm();
    }

    return TRUE;
}
