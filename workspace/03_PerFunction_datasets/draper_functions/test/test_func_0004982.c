signal_callback(void *arg)
{
    int rc = cr_checkpoint(CR_CHECKPOINT_READY);
    if (rc > 0) {
        execl("/bin/true", "true", NULL);
    }
    return 0;
}
