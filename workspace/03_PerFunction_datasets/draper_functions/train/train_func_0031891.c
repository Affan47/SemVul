client_ping_cbk (struct rpc_req *req, struct iovec *iov, int count,
                 void *myframe)
{
        xlator_t              *this    = NULL;
        rpc_clnt_connection_t *conn    = NULL;
        struct timeval         timeout = {0, };
        call_frame_t          *frame   = NULL;
        clnt_conf_t           *conf    = NULL;

        if (!myframe) {
                gf_log (THIS->name, GF_LOG_WARNING,
                        "frame with the request is NULL");
                goto out;
        }
        frame = myframe;
        this = frame->this;
        if (!this || !this->private) {
                gf_log (THIS->name, GF_LOG_WARNING,
                        "xlator private is not set");
                goto out;
        }

        conf = this->private;
        conn = &conf->rpc->conn;

        pthread_mutex_lock (&conn->lock);
        {
                if (req->rpc_status == -1) {
                        if (conn->ping_timer != NULL) {
                                gf_log (this->name, GF_LOG_WARNING,
                                        "socket or ib related error");
                                gf_timer_call_cancel (this->ctx,
                                                      conn->ping_timer);
                                conn->ping_timer = NULL;
                        } else {

                                gf_log (this->name, GF_LOG_WARNING,
                                        "timer must have expired");
                        }

                        goto unlock;
                }


                timeout.tv_sec  = conf->opt.ping_timeout;
                timeout.tv_usec = 0;

                gf_timer_call_cancel (this->ctx,
                                      conn->ping_timer);

                conn->ping_timer =
                        gf_timer_call_after (this->ctx, timeout,
                                             client_start_ping, (void *)this);

                if (conn->ping_timer == NULL)
                        gf_log (this->name, GF_LOG_WARNING,
                                "failed to set the ping timer");
        }
unlock:
        pthread_mutex_unlock (&conn->lock);
out:
        if (frame)
                STACK_DESTROY (frame->root);
        return 0;
}
