audacious_rc_status (RemoteObject * obj, char * * status, GError * * error)
{
    if (drct_get_playing ())
        * status = strdup (drct_get_paused () ? "paused" : "playing");
    else
        * status = strdup ("stopped");

    return TRUE;
}
