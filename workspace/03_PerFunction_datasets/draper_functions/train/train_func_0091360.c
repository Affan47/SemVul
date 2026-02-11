auth_gssapi_refresh(
     AUTH *auth,
     struct rpc_msg *msg)
{
     if (msg->rm_reply.rp_rjct.rj_stat == AUTH_ERROR &&
	 msg->rm_reply.rp_rjct.rj_why == AUTH_REJECTEDVERF) {
	  PRINTF(("gssapi_refresh: rejected verifier, incrementing\n"));
	  AUTH_PRIVATE(auth)->seq_num++;
	  return TRUE;
     } else {
	  PRINTF(("gssapi_refresh: failing\n"));
	  return FALSE;
     }
}
