error(int retval) {
    if (log_flags.async_file_debug) {
        msg_printf(fip->project, MSG_INFO,
            "[async] async verify of %s failed: %s",
            fip->name, boincerror(retval)
        );
    }
    fip->async_verify = NULL;
    fip->status = retval;
}
