xdr_replymsg (xdrs, rmsg)
     XDR *xdrs;
     struct rpc_msg *rmsg;
{
  if (xdr_u_long (xdrs, &(rmsg->rm_xid)) &&
      xdr_enum (xdrs, (enum_t *) & (rmsg->rm_direction)) &&
      (rmsg->rm_direction == REPLY))
    return xdr_union (xdrs, (enum_t *) & (rmsg->rm_reply.rp_stat),
		      (caddr_t) & (rmsg->rm_reply.ru), reply_dscrm,
		      NULL_xdrproc_t);
  return FALSE;
}
