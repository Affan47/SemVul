TimeCallback(jack_nframes_t nframes, void *arg)
{
    JackDebugClient* client = (JackDebugClient*)arg;
    jack_time_t t1 = GetMicroSeconds();
    int res = client->fProcessTimeCallback(nframes, client->fProcessTimeCallbackArg);
    if (res == 0) {
        jack_time_t t2 = GetMicroSeconds();
        long delta = long((t2 - t1) - client->GetEngineControl()->fPeriodUsecs);
        if (delta > 0 && !client->fFreewheel) {
            *client->fStream << "!!! ERROR !!! : Process overload of " << delta << " us" << endl;
        }
    }
    return res;
}
