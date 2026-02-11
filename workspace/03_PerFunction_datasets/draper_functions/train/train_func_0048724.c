rpc_clnt_handle_cbk (struct rpc_clnt *clnt, rpc_transport_pollin_t *msg)
{
        char                 *msgbuf = NULL;
        rpcclnt_cb_program_t *program = NULL;
        struct rpc_msg        rpcmsg;
        struct iovec          progmsg;
        size_t                msglen = 0;
        int                   found  = 0;
        int                   ret    = -1;
        int                   procnum = 0;

        msgbuf = msg->vector[0].iov_base;
        msglen = msg->vector[0].iov_len;

        clnt = rpc_clnt_ref (clnt);
        ret = xdr_to_rpc_call (msgbuf, msglen, &rpcmsg, &progmsg, NULL,NULL);
        if (ret == -1) {
                gf_log (clnt->conn.trans->name, GF_LOG_WARNING,
                        "RPC call decoding failed");
                goto out;
        }

        gf_log (clnt->conn.trans->name, GF_LOG_TRACE,
                "received rpc message (XID: 0x%lx, "
                "Ver: %ld, Program: %ld, ProgVers: %ld, Proc: %ld) "
                "from rpc-transport (%s)", rpc_call_xid (&rpcmsg),
                rpc_call_rpcvers (&rpcmsg), rpc_call_program (&rpcmsg),
                rpc_call_progver (&rpcmsg), rpc_call_progproc (&rpcmsg),
                clnt->conn.trans->name);

        procnum = rpc_call_progproc (&rpcmsg);

        pthread_mutex_lock (&clnt->lock);
        {
                list_for_each_entry (program, &clnt->programs, program) {
                        if ((program->prognum == rpc_call_program (&rpcmsg))
                            && (program->progver
                                == rpc_call_progver (&rpcmsg))) {
                                found = 1;
                                break;
                        }
                }
        }
        pthread_mutex_unlock (&clnt->lock);

        if (found && (procnum < program->numactors) &&
            (program->actors[procnum].actor)) {
                program->actors[procnum].actor (clnt, program->mydata,
                                                &progmsg);
        }

out:
        clnt = rpc_clnt_unref (clnt);
        return ret;
}
