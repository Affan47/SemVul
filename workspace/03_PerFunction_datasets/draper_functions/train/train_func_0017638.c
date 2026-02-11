_authenticate (register struct svc_req *rqst, struct rpc_msg *msg)
{
  register int cred_flavor;

  rqst->rq_cred = msg->rm_call.cb_cred;
  rqst->rq_xprt->xp_verf.oa_flavor = _null_auth.oa_flavor;
  rqst->rq_xprt->xp_verf.oa_length = 0;
  cred_flavor = rqst->rq_cred.oa_flavor;
  if ((cred_flavor <= AUTH_MAX) && (cred_flavor >= AUTH_NULL))
    return (*(svcauthsw[cred_flavor].authenticator)) (rqst, msg);

  return AUTH_REJECTEDCRED;
}
