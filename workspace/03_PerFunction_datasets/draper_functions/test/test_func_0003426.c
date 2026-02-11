operation_finished(mainloop_child_t * p, pid_t pid, int core, int signo, int exitcode)
{
    svc_action_t *op = mainloop_child_userdata(p);
    char *prefix = g_strdup_printf("%s:%d", op->id, op->pid);

    mainloop_clear_child_userdata(p);
    op->status = PCMK_LRM_OP_DONE;
    CRM_ASSERT(op->pid == pid);

    if (op->opaque->stderr_gsource) {


        dispatch_stderr(op);
    }

    if (op->opaque->stdout_gsource) {


        dispatch_stdout(op);
    }

    if (signo) {
        if (mainloop_child_timeout(p)) {
            crm_warn("%s - timed out after %dms", prefix, op->timeout);
            op->status = PCMK_LRM_OP_TIMEOUT;
            op->rc = PCMK_OCF_TIMEOUT;

        } else {
            crm_warn("%s - terminated with signal %d", prefix, signo);
            op->status = PCMK_LRM_OP_ERROR;
            op->rc = PCMK_OCF_SIGNAL;
        }

    } else {
        op->rc = exitcode;
        crm_debug("%s - exited with rc=%d", prefix, exitcode);
    }

    g_free(prefix);
    prefix = g_strdup_printf("%s:%d:stderr", op->id, op->pid);
    crm_log_output(LOG_NOTICE, prefix, op->stderr_data);

    g_free(prefix);
    prefix = g_strdup_printf("%s:%d:stdout", op->id, op->pid);
    crm_log_output(LOG_DEBUG, prefix, op->stdout_data);

    g_free(prefix);
    operation_finalize(op);
}
