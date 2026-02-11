process_ib_ipinfo(void *in_msg, void *out_msg, int op)
{
	struct hv_kvp_ip_msg *in = in_msg;
	struct hv_kvp_msg *out = out_msg;

	switch (op) {
	case KVP_OP_SET_IP_INFO:


		utf16s_to_utf8s((wchar_t *)in->kvp_ip_val.ip_addr,
				MAX_IP_ADDR_SIZE,
				UTF16_LITTLE_ENDIAN,
				(__u8 *)out->body.kvp_ip_val.ip_addr,
				MAX_IP_ADDR_SIZE);

		utf16s_to_utf8s((wchar_t *)in->kvp_ip_val.sub_net,
				MAX_IP_ADDR_SIZE,
				UTF16_LITTLE_ENDIAN,
				(__u8 *)out->body.kvp_ip_val.sub_net,
				MAX_IP_ADDR_SIZE);

		utf16s_to_utf8s((wchar_t *)in->kvp_ip_val.gate_way,
				MAX_GATEWAY_SIZE,
				UTF16_LITTLE_ENDIAN,
				(__u8 *)out->body.kvp_ip_val.gate_way,
				MAX_GATEWAY_SIZE);

		utf16s_to_utf8s((wchar_t *)in->kvp_ip_val.dns_addr,
				MAX_IP_ADDR_SIZE,
				UTF16_LITTLE_ENDIAN,
				(__u8 *)out->body.kvp_ip_val.dns_addr,
				MAX_IP_ADDR_SIZE);

		out->body.kvp_ip_val.dhcp_enabled = in->kvp_ip_val.dhcp_enabled;

	default:
		utf16s_to_utf8s((wchar_t *)in->kvp_ip_val.adapter_id,
				MAX_ADAPTER_ID_SIZE,
				UTF16_LITTLE_ENDIAN,
				(__u8 *)out->body.kvp_ip_val.adapter_id,
				MAX_ADAPTER_ID_SIZE);

		out->body.kvp_ip_val.addr_family = in->kvp_ip_val.addr_family;
	}
}
