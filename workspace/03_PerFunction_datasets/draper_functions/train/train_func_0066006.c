rpcsvc_check_and_reply_error (int ret, call_frame_t *frame, void *opaque)
{
	rpcsvc_request_t  *req = NULL;

	req = opaque;

        if (ret)
                gf_log ("rpcsvc", GF_LOG_ERROR,
                        "rpc actor failed to complete successfully");

        if (ret == RPCSVC_ACTOR_ERROR) {
                ret = rpcsvc_error_reply (req);
                if (ret)
                        gf_log ("rpcsvc", GF_LOG_WARNING,
                                "failed to queue error reply");
        }

	return 0;
}
