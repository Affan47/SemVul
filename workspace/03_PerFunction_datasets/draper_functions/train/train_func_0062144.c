write_netgroup(nssov_netgroup_cbp *cbp,Entry *entry)
{
	int32_t tmpint32;
	int i;
	Attribute *a;


	a = attr_find(entry->e_attrs,cbp->mi->mi_attrs[1].an_desc);
	if ( a ) {

		for (i=0;i<a->a_numvals;i++)
		{
			if (write_netgroup_triple(cbp->fp, a->a_vals[i].bv_val))
				return -1;
		}
	}
	a = attr_find(entry->e_attrs,cbp->mi->mi_attrs[2].an_desc);
	if ( a ) {

		for (i=0;i<a->a_numvals;i++)
		{

			WRITE_INT32(cbp->fp,NSLCD_RESULT_BEGIN);

			WRITE_INT32(cbp->fp,NSLCD_NETGROUP_TYPE_NETGROUP);

			if (write_string_stripspace_len(cbp->fp,a->a_vals[i].bv_val,a->a_vals[i].bv_len))
				return -1;
		}
	}

	return 0;
}
