dissect_pkcs12_T_crlValue(gboolean implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 120 "../../asn1/pkcs12/pkcs12.cnf"
	if(object_identifier_id)
		offset = call_ber_oid_callback(object_identifier_id, tvb, offset, actx->pinfo, tree, NULL);


  return offset;
}
