xdr_group_obj (XDR *xdrs, group_obj *objp)
{
  bool_t res = xdr_u_int (xdrs, &objp->gr_flags);
  if (__builtin_expect (res, TRUE))
    res = xdr_array (xdrs, (void *) &objp->gr_members.gr_members_val,
		     &objp->gr_members.gr_members_len, ~0,
		     sizeof (nis_name), (xdrproc_t) _xdr_nis_name);
  return res;
}
