stun_is_challenge_response_str(const u08bits* buf, size_t len, int *err_code, u08bits *err_msg, size_t err_msg_size,
				u08bits *realm, u08bits *nonce)
{
	int ret = stun_is_error_response_str(buf, len, err_code, err_msg, err_msg_size);

	if(ret && (((*err_code) == 401) || ((*err_code) == 438) || ((*err_code) == SHA_TOO_WEAK))) {

		stun_attr_ref sar = stun_attr_get_first_by_type_str(buf,len,STUN_ATTRIBUTE_REALM);
		if(sar) {
			const u08bits *value = stun_attr_get_value(sar);
			if(value) {
				size_t vlen = (size_t)stun_attr_get_len(sar);
				ns_bcopy(value,realm,vlen);
				realm[vlen]=0;
				sar = stun_attr_get_first_by_type_str(buf,len,STUN_ATTRIBUTE_NONCE);
				if(sar) {
					value = stun_attr_get_value(sar);
					if(value) {
						vlen = (size_t)stun_attr_get_len(sar);
						ns_bcopy(value,nonce,vlen);
						nonce[vlen]=0;
						return 1;
					}
				}
			}
		}
	}

	return 0;
}
