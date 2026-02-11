xdr_objdata (XDR *xdrs, objdata *objp)
{
  bool_t res = xdr_zotypes (xdrs, &objp->zo_type);
  if (!__builtin_expect (res, TRUE))
    return res;
  switch (objp->zo_type)
    {
    case NIS_DIRECTORY_OBJ:
      return _xdr_directory_obj (xdrs, &objp->objdata_u.di_data);
    case NIS_GROUP_OBJ:
      return xdr_group_obj (xdrs, &objp->objdata_u.gr_data);
    case NIS_TABLE_OBJ:
      return xdr_table_obj (xdrs, &objp->objdata_u.ta_data);
    case NIS_ENTRY_OBJ:
      return xdr_entry_obj (xdrs, &objp->objdata_u.en_data);
    case NIS_LINK_OBJ:
      return xdr_link_obj (xdrs, &objp->objdata_u.li_data);
    case NIS_PRIVATE_OBJ:
      return xdr_bytes (xdrs, &objp->objdata_u.po_data.po_data_val,
			&objp->objdata_u.po_data.po_data_len, ~0);
    case NIS_NO_OBJ:
    case NIS_BOGUS_OBJ:
    default:
      return TRUE;
    }
}
