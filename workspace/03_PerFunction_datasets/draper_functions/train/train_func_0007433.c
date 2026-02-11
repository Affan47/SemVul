stop_child(pcmk_child_t * child, int signal)
{
    if (signal == 0) {
        signal = SIGTERM;
    }

    if (child->command == NULL) {
        crm_debug("Nothing to do for child \"%s\"", child->name);
        return TRUE;
    }

    if (child->pid <= 0) {
        crm_trace("Client %s not running", child->name);
        return TRUE;
    }

    errno = 0;
    if (kill(child->pid, signal) == 0) {
        crm_notice("Stopping %s: Sent -%d to process %d", child->name, signal, child->pid);

    } else {
        crm_perror(LOG_ERR, "Stopping %s: Could not send -%d to process %d failed",
                   child->name, signal, child->pid);
    }

    return TRUE;
}
