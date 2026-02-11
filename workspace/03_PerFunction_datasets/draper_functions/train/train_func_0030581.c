xdr_krb5_key_data(XDR *xdrs, krb5_key_data *objp)
{
    unsigned int tmp;

    if (!xdr_krb5_int16(xdrs, &objp->key_data_ver))
	return(FALSE);
    if (!xdr_krb5_int16(xdrs, &objp->key_data_kvno))
	return(FALSE);
    if (!xdr_krb5_int16(xdrs, &objp->key_data_type[0]))
	return(FALSE);
    if (!xdr_krb5_int16(xdrs, &objp->key_data_type[1]))
	return(FALSE);
    if (!xdr_krb5_ui_2(xdrs, &objp->key_data_length[0]))
	return(FALSE);
    if (!xdr_krb5_ui_2(xdrs, &objp->key_data_length[1]))
	return(FALSE);

    tmp = (unsigned int) objp->key_data_length[0];
    if (!xdr_bytes(xdrs, (char **) &objp->key_data_contents[0],
		   &tmp, ~0))
	return FALSE;

    tmp = (unsigned int) objp->key_data_length[1];
    if (!xdr_bytes(xdrs, (char **) &objp->key_data_contents[1],
		   &tmp, ~0))
	return FALSE;


    return(TRUE);
}
