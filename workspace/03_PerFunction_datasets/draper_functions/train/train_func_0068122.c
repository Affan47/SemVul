Notify(int refnum, int notify, int value)
{
    JackClientNotificationRequest req(refnum, notify, value);
    if (req.Write(&fRequestSocket) < 0) {
        jack_error("Could not write notification ref = %d notify = %d", refnum, notify);
    }
}
