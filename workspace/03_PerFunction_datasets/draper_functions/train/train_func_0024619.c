dissect_ldap_T_intermediateResponse_responseValue(gboolean implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 755 "../../asn1/ldap/ldap.cnf"

	const gchar *name;


#line 759 "../../asn1/ldap/ldap.cnf"
	if(ldm_tree && object_identifier_id) {
		proto_item_set_text(ldm_tree, "%s %s", "IntermediateResponse", object_identifier_id);
		name = oid_resolved_from_string(object_identifier_id);
		if(name)
			proto_item_append_text(ldm_tree, " (%s)", name);
	}
	if((object_identifier_id != NULL) && oid_has_dissector(object_identifier_id)) {
		offset = call_ber_oid_callback(object_identifier_id, tvb, offset, actx->pinfo, tree, NULL);
	} else {
		  offset = dissect_ber_octet_string(implicit_tag, actx, tree, tvb, offset, hf_index,
                                       NULL);

	}


  return offset;
}
