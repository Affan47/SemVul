SPF_c_parse_cidr(SPF_response_t *spf_response,
				SPF_data_cidr_t *data,
				const char *src, size_t *src_len)
{
	SPF_errcode_t	 err;
	size_t			 idx;

	memset(data, 0, sizeof(SPF_data_cidr_t));
	data->parm_type = PARM_CIDR;


	idx = *src_len - 1;
	while (idx > 0 && isdigit( (unsigned char)(src[idx]) ))
		idx--;


	if (idx < (*src_len - 1) && src[idx] == '/') {
		if (idx > 0 && src[idx - 1] == '/') {

			err = SPF_c_parse_cidr_ip6(spf_response, &data->ipv6, &src[idx]);
			if (err)
				return err;

			*src_len = idx - 1;
			idx = *src_len - 1;
			while (idx > 0 && isdigit( (unsigned char)(src[idx]) ))
				idx--;


			if (idx < (*src_len - 1) && src[idx] == '/') {


				err = SPF_c_parse_cidr_ip4(spf_response, &data->ipv4, &src[idx]);
				if (err)
					return err;
				*src_len = idx;
			}
		}
		else {

			err = SPF_c_parse_cidr_ip4(spf_response, &data->ipv4, &src[idx]);
			if (err)
				return err;
			*src_len = idx;
		}
	}

	return SPF_E_SUCCESS;
}
