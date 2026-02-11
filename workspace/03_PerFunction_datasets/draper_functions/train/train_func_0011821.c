ProcessNext(jack_time_t cur_cycle_begin)
{
    fLastSwitchUsecs = cur_cycle_begin;
    if (fGraphManager->RunNextGraph())  {
        fChannel.Notify(ALL_CLIENTS, kGraphOrderCallback, 0);
    }
    fSignal.Signal();
}
