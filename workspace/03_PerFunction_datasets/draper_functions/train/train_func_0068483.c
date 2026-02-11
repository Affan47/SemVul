dissect_ldap_oid(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree)
{
	char *oid;
	const char *oidname;


	oid=tvb_get_string_enc(wmem_packet_scope(), tvb, 0, tvb_reported_length(tvb), ENC_UTF_8|ENC_NA);
	if(!oid){
		return;
	}

	oidname=oid_resolved_from_string(oid);

	if(oidname){
		proto_tree_add_string_format_value(tree, hf_ldap_oid, tvb, 0, tvb_reported_length(tvb), oid, "%s (%s)",oid,oidname);
	} else {
		proto_tree_add_string(tree, hf_ldap_oid, tvb, 0, tvb_captured_length(tvb), oid);
	}
}
