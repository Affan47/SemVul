ipsec_is_attribute_incompatible(u_int16_t type, u_int8_t *value, u_int16_t len,
    void *vmsg)
{
	struct message *msg = vmsg;
	u_int16_t dv = decode_16(value);

	if (msg->exchange->phase == 1) {
		switch (type) {
		case IKE_ATTR_ENCRYPTION_ALGORITHM:
			return !crypto_get(from_ike_crypto(dv));
		case IKE_ATTR_HASH_ALGORITHM:
			return !hash_get(from_ike_hash(dv));
		case IKE_ATTR_AUTHENTICATION_METHOD:
			return !ike_auth_get(dv);
		case IKE_ATTR_GROUP_DESCRIPTION:
			return (dv < IKE_GROUP_DESC_MODP_768
				|| dv > IKE_GROUP_DESC_MODP_1536)
			    && (dv < IKE_GROUP_DESC_MODP_2048
				|| dv > IKE_GROUP_DESC_MODP_8192);
		case IKE_ATTR_GROUP_TYPE:
			return 1;
		case IKE_ATTR_GROUP_PRIME:
			return 1;
		case IKE_ATTR_GROUP_GENERATOR_1:
			return 1;
		case IKE_ATTR_GROUP_GENERATOR_2:
			return 1;
		case IKE_ATTR_GROUP_CURVE_A:
			return 1;
		case IKE_ATTR_GROUP_CURVE_B:
			return 1;
		case IKE_ATTR_LIFE_TYPE:
			return dv < IKE_DURATION_SECONDS
			    || dv > IKE_DURATION_KILOBYTES;
		case IKE_ATTR_LIFE_DURATION:
			return len != 2 && len != 4;
		case IKE_ATTR_PRF:
			return 1;
		case IKE_ATTR_KEY_LENGTH:


			return dv % 8 != 0;
		case IKE_ATTR_FIELD_SIZE:
			return 1;
		case IKE_ATTR_GROUP_ORDER:
			return 1;
		}
	} else {
		switch (type) {
		case IPSEC_ATTR_SA_LIFE_TYPE:
			return dv < IPSEC_DURATION_SECONDS
			    || dv > IPSEC_DURATION_KILOBYTES;
		case IPSEC_ATTR_SA_LIFE_DURATION:
			return len != 2 && len != 4;
		case IPSEC_ATTR_GROUP_DESCRIPTION:
			return (dv < IKE_GROUP_DESC_MODP_768
				|| dv > IKE_GROUP_DESC_MODP_1536)
			    && (dv < IKE_GROUP_DESC_MODP_2048
				|| IKE_GROUP_DESC_MODP_8192 < dv);
		case IPSEC_ATTR_ENCAPSULATION_MODE:
#if defined (USE_NAT_TRAVERSAL)
			return dv != IPSEC_ENCAP_TUNNEL
			    && dv != IPSEC_ENCAP_TRANSPORT
			    && dv != IPSEC_ENCAP_UDP_ENCAP_TUNNEL
			    && dv != IPSEC_ENCAP_UDP_ENCAP_TRANSPORT
			    && dv != IPSEC_ENCAP_UDP_ENCAP_TUNNEL_DRAFT
			    && dv != IPSEC_ENCAP_UDP_ENCAP_TRANSPORT_DRAFT;
#else
			return dv < IPSEC_ENCAP_TUNNEL
			    || dv > IPSEC_ENCAP_TRANSPORT;
#endif
		case IPSEC_ATTR_AUTHENTICATION_ALGORITHM:
			return dv < IPSEC_AUTH_HMAC_MD5
			    || dv > IPSEC_AUTH_HMAC_RIPEMD;
		case IPSEC_ATTR_KEY_LENGTH:


			return 0;
		case IPSEC_ATTR_KEY_ROUNDS:
			return 1;
		case IPSEC_ATTR_COMPRESS_DICTIONARY_SIZE:
			return 1;
		case IPSEC_ATTR_COMPRESS_PRIVATE_ALGORITHM:
			return 1;
		case IPSEC_ATTR_ECN_TUNNEL:
			return 1;
		}
	}

	return 1;
}
