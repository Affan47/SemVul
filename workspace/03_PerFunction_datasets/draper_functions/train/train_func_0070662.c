rpcsvc_program_actor (rpcsvc_request_t *req)
{
        rpcsvc_program_t        *program = NULL;
        int                     err      = SYSTEM_ERR;
        rpcsvc_actor_t          *actor   = NULL;
        rpcsvc_t                *svc     = NULL;
        char                    found    = 0;

        if (!req)
                goto err;

        svc = req->svc;
        pthread_mutex_lock (&svc->rpclock);
        {
                list_for_each_entry (program, &svc->programs, program) {
                        if (program->prognum == req->prognum) {
                                err = PROG_MISMATCH;
                        }

                        if ((program->prognum == req->prognum)
                            && (program->progver == req->progver)) {
                                found = 1;
                                break;
                        }
                }
        }
        pthread_mutex_unlock (&svc->rpclock);

        if (!found) {
                if (err != PROG_MISMATCH) {


                        gf_log (GF_RPCSVC, (req->prognum == ACL_PROGRAM) ?
                                GF_LOG_DEBUG : GF_LOG_WARNING,
                                "RPC program not available (req %u %u)",
                                req->prognum, req->progver);
                        err = PROG_UNAVAIL;
                        goto err;
                }

                gf_log (GF_RPCSVC, GF_LOG_WARNING,
                        "RPC program version not available (req %u %u)",
                        req->prognum, req->progver);
                goto err;
        }
        req->prog = program;
        if (!program->actors) {
                gf_log (GF_RPCSVC, GF_LOG_WARNING,
                        "RPC Actor not found for program %s %d",
                        program->progname, program->prognum);
                err = SYSTEM_ERR;
                goto err;
        }

        if ((req->procnum < 0) || (req->procnum >= program->numactors)) {
                gf_log (GF_RPCSVC, GF_LOG_ERROR, "RPC Program procedure not"
                        " available for procedure %d in %s", req->procnum,
                        program->progname);
                err = PROC_UNAVAIL;
                goto err;
        }

        actor = &program->actors[req->procnum];
        if (!actor->actor) {
                gf_log (GF_RPCSVC, GF_LOG_ERROR, "RPC Program procedure not"
                        " available for procedure %d in %s", req->procnum,
                        program->progname);
                err = PROC_UNAVAIL;
                actor = NULL;
                goto err;
        }

	req->synctask = program->synctask;

        err = SUCCESS;
        gf_log (GF_RPCSVC, GF_LOG_TRACE, "Actor found: %s - %s",
                program->progname, actor->procname);
err:
        if (req)
                req->rpc_err = err;

        return actor;
}
