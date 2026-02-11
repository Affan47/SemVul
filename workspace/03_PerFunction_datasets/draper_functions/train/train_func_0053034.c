rpcclnt_cbk_program_register (struct rpc_clnt *clnt,
                              rpcclnt_cb_program_t *program, void *mydata)
{
        int                   ret                = -1;
        char                  already_registered = 0;
        rpcclnt_cb_program_t *tmp                = NULL;

        if (!clnt)
                goto out;

        if (program->actors == NULL)
                goto out;

        pthread_mutex_lock (&clnt->lock);
        {
                list_for_each_entry (tmp, &clnt->programs, program) {
                        if ((program->prognum == tmp->prognum)
                            && (program->progver == tmp->progver)) {
                                already_registered = 1;
                                break;
                        }
                }
        }
        pthread_mutex_unlock (&clnt->lock);

        if (already_registered) {
                gf_log_callingfn (clnt->conn.trans->name, GF_LOG_DEBUG,
                                  "already registered");
                ret = 0;
                goto out;
        }

        tmp = GF_CALLOC (1, sizeof (*tmp),
                         gf_common_mt_rpcclnt_cb_program_t);
        if (tmp == NULL) {
                goto out;
        }

        memcpy (tmp, program, sizeof (*tmp));
        INIT_LIST_HEAD (&tmp->program);

        tmp->mydata = mydata;

        pthread_mutex_lock (&clnt->lock);
        {
                list_add_tail (&tmp->program, &clnt->programs);
        }
        pthread_mutex_unlock (&clnt->lock);

        ret = 0;
        gf_log (clnt->conn.trans->name, GF_LOG_DEBUG,
                "New program registered: %s, Num: %d, Ver: %d",
                program->progname, program->prognum,
                program->progver);

out:
        if (ret == -1) {
                gf_log (clnt->conn.trans->name, GF_LOG_ERROR,
                        "Program registration failed:"
                        " %s, Num: %d, Ver: %d", program->progname,
                        program->prognum, program->progver);
        }

        return ret;
}
