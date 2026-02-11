SetSampleRateCallback(JackSampleRateCallback callback, void *arg)
{
    if (IsActive()) {
        jack_error("You cannot set callbacks on an active client");
        return -1;
    } else {
        GetClientControl()->fCallback[kSampleRateCallback] = (callback != NULL);
        fSampleRateArg = arg;
        fSampleRate = callback;

        if (callback) {
            callback(GetEngineControl()->fSampleRate, arg);
        }
        return 0;
    }
}
