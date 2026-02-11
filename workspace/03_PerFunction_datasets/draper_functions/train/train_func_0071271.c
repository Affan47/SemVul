xdr_dis_data_query_pdu(xdrs, objp)
	XDR *xdrs;
	dis_data_query_pdu *objp;
{
	if (!xdr_dis_pdu_header(xdrs, &objp->hdr)) {
		return (FALSE);
	}
	if (!xdr_dis_entity_id(xdrs, &objp->orig_id)) {
		return (FALSE);
	}
	if (!xdr_dis_entity_id(xdrs, &objp->recv_id)) {
		return (FALSE);
	}
	if (!xdr_dis_time(xdrs, &objp->interval)) {
		return (FALSE);
	}
	if (!xdr_dis_request_id(xdrs, &objp->request_id)) {
		return (FALSE);
	}
	if (!xdr_byte_u_long(xdrs, &objp->num_fixed_data)) {
		return (FALSE);
	}
	if (!xdr_byte_u_long(xdrs, &objp->num_variable_data)) {
		return (FALSE);
	}
	if (!xdr_var_array(xdrs, (char **)&objp->fixed_datum_id,
		objp->num_fixed_data, objp->num_fixed_data, sizeof(byte_u_long), xdr_byte_u_long)) {
		return (FALSE);
	}
	if (!xdr_var_array(xdrs, (char **)&objp->variable_datum_id,
		objp->num_variable_data, objp->num_variable_data, sizeof(byte_u_long), xdr_byte_u_long)) {
		return (FALSE);
	}
	return (TRUE);
}
