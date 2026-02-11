xdr_time_t(XDR *xdrs, time_t *tp)
{
	int32_t i;

	switch (xdrs->x_op) {
	case XDR_ENCODE:


        if (*tp > INT32_MAX)
            *tp = INT32_MAX;
        else if (*tp < INT32_MIN)
            *tp = INT32_MIN;

		i =  (int32_t)*tp;
		return (XDR_PUTINT32(xdrs, &i));

	case XDR_DECODE:
		if (!XDR_GETINT32(xdrs, &i))
			return (FALSE);
		*tp = (time_t)i;
		return (TRUE);

	case XDR_FREE:
		return (TRUE);
	}
	return (FALSE);
}
