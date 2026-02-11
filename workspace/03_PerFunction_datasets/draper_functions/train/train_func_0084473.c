alarm_applet_alarm_snooze (AlarmApplet *applet, Alarm *alarm)
{
    guint mins = applet->snooze_mins;

    if (alarm->type == ALARM_TYPE_CLOCK) {

        mins = ALARM_STD_SNOOZE;
    }

    g_debug ("AlarmApplet: snooze '%s' for %d minutes", alarm->message, mins);

    alarm_snooze (alarm, mins * 60);


    alarm_applet_status_update (applet);
}
