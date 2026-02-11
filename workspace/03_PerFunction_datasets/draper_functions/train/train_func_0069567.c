xdr_gf_notify_rsp (XDR *xdrs, gf_notify_rsp *objp)
{
	register int32_t *buf;
        buf = NULL;


	if (xdrs->x_op == XDR_ENCODE) {
		buf = XDR_INLINE (xdrs, 3 * BYTES_PER_XDR_UNIT);
		if (buf == NULL) {
			 if (!xdr_int (xdrs, &objp->op_ret))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->op_errno))
				 return FALSE;
			 if (!xdr_u_int (xdrs, &objp->flags))
				 return FALSE;

		} else {
		IXDR_PUT_LONG(buf, objp->op_ret);
		IXDR_PUT_LONG(buf, objp->op_errno);
		IXDR_PUT_U_LONG(buf, objp->flags);
		}
		 if (!xdr_string (xdrs, &objp->buf, ~0))
			 return FALSE;
		 if (!xdr_bytes (xdrs, (char **)&objp->xdata.xdata_val, (u_int *) &objp->xdata.xdata_len, ~0))
			 return FALSE;
		return TRUE;
	} else if (xdrs->x_op == XDR_DECODE) {
		buf = XDR_INLINE (xdrs, 3 * BYTES_PER_XDR_UNIT);
		if (buf == NULL) {
			 if (!xdr_int (xdrs, &objp->op_ret))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->op_errno))
				 return FALSE;
			 if (!xdr_u_int (xdrs, &objp->flags))
				 return FALSE;

		} else {
		objp->op_ret = IXDR_GET_LONG(buf);
		objp->op_errno = IXDR_GET_LONG(buf);
		objp->flags = IXDR_GET_U_LONG(buf);
		}
		 if (!xdr_string (xdrs, &objp->buf, ~0))
			 return FALSE;
		 if (!xdr_bytes (xdrs, (char **)&objp->xdata.xdata_val, (u_int *) &objp->xdata.xdata_len, ~0))
			 return FALSE;
	 return TRUE;
	}

	 if (!xdr_int (xdrs, &objp->op_ret))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->op_errno))
		 return FALSE;
	 if (!xdr_u_int (xdrs, &objp->flags))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->buf, ~0))
		 return FALSE;
	 if (!xdr_bytes (xdrs, (char **)&objp->xdata.xdata_val, (u_int *) &objp->xdata.xdata_len, ~0))
		 return FALSE;
	return TRUE;
}
