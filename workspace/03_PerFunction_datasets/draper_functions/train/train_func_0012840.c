hooks_precheckpoint(void *p)
{
    CRUT_DEBUG("Preparing to checkpoint.");

    return check_event(-1);
}
