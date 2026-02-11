pv_get_branch_fields(struct sip_msg *msg, pv_param_t *param,
		pv_value_t *res)
{
	str uri;
	qvalue_t q;
	int idx;
	int idxf;
	char *p;

	if(msg==NULL || res==NULL)
		return -1;

	if(msg->first_line.type == SIP_REPLY || nr_branches==0 )
		return pv_get_null(msg, param, res);


	if(pv_get_spec_index(msg, param, &idx, &idxf)!=0) {
		LM_ERR("invalid index\n");
		return -1;
	}

	if ( (idxf==0 || idxf==PV_IDX_INT) && idx==0) {

		return get_branch_field( 0, &param->pvn, res);
	}

	if(idxf==PV_IDX_ALL) {

		p = pv_local_buf;
		idx = 0;

		while ( (uri.s=get_branch(idx, &uri.len, &q, 0, 0, 0, 0))!=NULL ) {

			if ( pv_local_buf + PV_LOCAL_BUF_SIZE <=
			p + uri.len + PV_FIELD_DELIM_LEN ) {
				LM_ERR("local buffer length exceeded\n");
				return pv_get_null(msg, param, res);
			}

			if (idx) {
				memcpy(p, PV_FIELD_DELIM, PV_FIELD_DELIM_LEN);
				p += PV_FIELD_DELIM_LEN;
			}

			memcpy(p, uri.s, uri.len);
			p += uri.len;
			idx++;
		}

		res->rs.s = pv_local_buf;
		res->rs.len = p - pv_local_buf;
		res->flags = PV_VAL_STR;
		return 0;
	}


	if (idx<0) {

		if (-idx > nr_branches)
			return pv_get_null(msg, param, res);
		idx = nr_branches - idx;
	}


	return get_branch_field( idx, &param->pvn, res);
}
