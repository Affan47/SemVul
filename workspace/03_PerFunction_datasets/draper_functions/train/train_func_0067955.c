xdr_ypresp_all (XDR *xdrs, ypresp_all *objp)
{
  if (!xdr_bool (xdrs, &objp->more))
    return FALSE;
  switch (objp->more)
    {
    case TRUE:
      return xdr_ypresp_key_val (xdrs, &objp->ypresp_all_u.val);
    case FALSE:
      break;
    default:
      return FALSE;
    }
  return TRUE;
}
