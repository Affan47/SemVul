call_bail (void *data)
{
        struct rpc_clnt       *clnt = NULL;
        rpc_clnt_connection_t *conn = NULL;
        struct timeval         current;
        struct list_head       list;
        struct saved_frame    *saved_frame = NULL;
        struct saved_frame    *trav = NULL;
        struct saved_frame    *tmp = NULL;
        struct tm              frame_sent_tm;
        char                   frame_sent[256] = {0,};
        struct timeval         timeout = {0,};
        struct iovec           iov = {0,};

        GF_VALIDATE_OR_GOTO ("client", data, out);

        clnt = data;

        conn = &clnt->conn;

        gettimeofday (&current, NULL);
        INIT_LIST_HEAD (&list);

        pthread_mutex_lock (&conn->lock);
        {


                if (conn->timer) {
                        timeout.tv_sec = 10;
                        timeout.tv_usec = 0;

                        gf_timer_call_cancel (clnt->ctx, conn->timer);
                        conn->timer = gf_timer_call_after (clnt->ctx,
                                                           timeout,
                                                           call_bail,
                                                           (void *) clnt);

                        if (conn->timer == NULL) {
                                gf_log (conn->trans->name, GF_LOG_WARNING,
                                        "Cannot create bailout timer");
                        }
                }

                do {
                        saved_frame =
                                __saved_frames_get_timedout (conn->saved_frames,
                                                             conn->frame_timeout,
                                                             &current);
                        if (saved_frame)
                                list_add (&saved_frame->list, &list);

                } while (saved_frame);
        }
        pthread_mutex_unlock (&conn->lock);

        list_for_each_entry_safe (trav, tmp, &list, list) {
                localtime_r (&trav->saved_at.tv_sec, &frame_sent_tm);
                strftime (frame_sent, 32, "%Y-%m-%d %H:%M:%S", &frame_sent_tm);
                snprintf (frame_sent + strlen (frame_sent),
                          256 - strlen (frame_sent),
                          ".%"GF_PRI_SUSECONDS, trav->saved_at.tv_usec);

		gf_log (conn->trans->name, GF_LOG_ERROR,
			"bailing out frame type(%s) op(%s(%d)) xid = 0x%ux "
                        "sent = %s. timeout = %d",
			trav->rpcreq->prog->progname,
                        (trav->rpcreq->prog->procnames) ?
                        trav->rpcreq->prog->procnames[trav->rpcreq->procnum] :
                        "--",
                        trav->rpcreq->procnum, trav->rpcreq->xid, frame_sent,
                        conn->frame_timeout);

                clnt = rpc_clnt_ref (clnt);
                trav->rpcreq->rpc_status = -1;
		trav->rpcreq->cbkfn (trav->rpcreq, &iov, 1, trav->frame);

                rpc_clnt_reply_deinit (trav->rpcreq, clnt->reqpool);
                clnt = rpc_clnt_unref (clnt);
                list_del_init (&trav->list);
                mem_put (trav);
        }
out:
        return;
}
