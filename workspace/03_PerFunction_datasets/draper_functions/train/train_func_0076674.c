dissect_snmp_T_encryptedPDU(gboolean implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 123 "../../asn1/snmp/snmp.cnf"
	tvbuff_t* crypt_tvb;
	offset = dissect_ber_octet_string(FALSE, actx, tree, tvb, offset, hf_snmp_encryptedPDU, &crypt_tvb);

	if( usm_p.encrypted && crypt_tvb
		&& usm_p.user_assoc
		&& usm_p.user_assoc->user.privProtocol ) {

		const gchar* error = NULL;
		proto_tree* encryptedpdu_tree = proto_item_add_subtree(actx->created_item,ett_encryptedPDU);
		tvbuff_t* cleartext_tvb = usm_p.user_assoc->user.privProtocol(&usm_p, crypt_tvb, &error );

		if (! cleartext_tvb) {
			proto_tree_add_expert_format(encryptedpdu_tree, actx->pinfo, &ei_snmp_failed_decrypted_data_pdu,
				crypt_tvb, 0, -1, "Failed to decrypt encryptedPDU: %s", error);

			col_set_str(actx->pinfo->cinfo, COL_INFO, "encryptedPDU: Failed to decrypt");

			return offset;
		} else {
			proto_item* decrypted_item;
			proto_tree* decrypted_tree;

			if (! check_ScopedPdu(cleartext_tvb)) {
				proto_tree_add_expert(encryptedpdu_tree, actx->pinfo, &ei_snmp_decrypted_data_bad_formatted, cleartext_tvb, 0, -1);

				col_set_str(actx->pinfo->cinfo, COL_INFO, "encryptedPDU: Decrypted data not formatted as expected");

				return offset;
			}


			add_new_data_source(actx->pinfo, cleartext_tvb, "Decrypted ScopedPDU");

			decrypted_item = proto_tree_add_item(encryptedpdu_tree, hf_snmp_decryptedPDU,cleartext_tvb,0,-1,ENC_NA);
			decrypted_tree = proto_item_add_subtree(decrypted_item,ett_decrypted);
			dissect_snmp_ScopedPDU(FALSE, cleartext_tvb, 0, actx, decrypted_tree, -1);
			}
	} else {
			col_set_str(actx->pinfo->cinfo, COL_INFO, "encryptedPDU: privKey Unknown");
	}


  return offset;
}
