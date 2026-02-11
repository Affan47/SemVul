odls_default_fork_local_proc(orte_app_context_t* context,
                                        orte_proc_t *child,
                                        char **environ_copy,
                                        orte_job_t *jobdat)
{
    orte_iof_base_io_conf_t opts;
    int rc, p[2];
    pid_t pid;

    if (NULL != child) {


        opts.usepty = OPAL_ENABLE_PTY_SUPPORT;


        if (NULL != child &&
            (jobdat->stdin_target == ORTE_VPID_WILDCARD ||
             child->name.vpid == jobdat->stdin_target)) {
            opts.connect_stdin = true;
        } else {
            opts.connect_stdin = false;
        }

        if (ORTE_SUCCESS != (rc = orte_iof_base_setup_prefork(&opts))) {
            ORTE_ERROR_LOG(rc);
            if (NULL != child) {
                child->state = ORTE_PROC_STATE_FAILED_TO_START;
                child->exit_code = rc;
            }
            return rc;
        }
    }


    if (pipe(p) < 0) {
        ORTE_ERROR_LOG(ORTE_ERR_SYS_LIMITS_PIPES);
        if (NULL != child) {
            child->state = ORTE_PROC_STATE_FAILED_TO_START;
            child->exit_code = ORTE_ERR_SYS_LIMITS_PIPES;
        }
        return ORTE_ERR_SYS_LIMITS_PIPES;
    }


    pid = fork();
    if (NULL != child) {
        child->pid = pid;
    }

    if (pid < 0) {
        ORTE_ERROR_LOG(ORTE_ERR_SYS_LIMITS_CHILDREN);
        if (NULL != child) {
            child->state = ORTE_PROC_STATE_FAILED_TO_START;
            child->exit_code = ORTE_ERR_SYS_LIMITS_CHILDREN;
        }
        return ORTE_ERR_SYS_LIMITS_CHILDREN;
    }

    if (pid == 0) {
	close(p[0]);
#if HAVE_SETPGID
        setpgid(0, 0);
#endif
        do_child(context, child, environ_copy, jobdat, p[1], opts);

    }

    close(p[1]);
    return do_parent(context, child, environ_copy, jobdat, p[0], opts);
}
