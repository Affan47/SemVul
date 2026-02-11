GetLowTic(void)
{
    int lowtic;

    lowtic = maketic;

#ifdef FEATURE_MULTIPLAYER
    if (net_client_connected)
    {
        if (drone || recvtic < lowtic)
        {
            lowtic = recvtic;
        }
    }
#endif

    return lowtic;
}
