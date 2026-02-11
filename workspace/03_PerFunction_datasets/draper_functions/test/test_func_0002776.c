handle_signal(int sig)
{
    process_state = -2;
    if (! signal_semaphore(connect_semaphore)) {

        die(SOURCE_SIGNAL_SEMAPHORE, get_semaphore_error());
    }
    if (! signal_semaphore(process_semaphore)) {

        die(SOURCE_SIGNAL_SEMAPHORE, get_semaphore_error());
    }
}
