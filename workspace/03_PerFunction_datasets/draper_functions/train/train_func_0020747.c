OnInfoShutdown(JackInfoShutdownCallback callback, void *arg)
{
    if (IsActive()) {
        jack_error("You cannot set callbacks on an active client");
    } else {

        GetClientControl()->fCallback[kShutDownCallback] = (callback != NULL);
        fInfoShutdownArg = arg;
        fInfoShutdown = callback;
    }
}
