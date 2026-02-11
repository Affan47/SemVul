dissect_tcap_DestTransactionID(gboolean implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 165 "../../asn1/tcap/tcap.cnf"
tvbuff_t *parameter_tvb;
guint8 len , i;
proto_tree *subtree;
subtree = proto_tree_add_subtree(tree, tvb, offset, -1, ett_dtid, NULL, "Destination Transaction ID");

dissect_ber_octet_string(implicit_tag, actx, subtree, tvb, offset, hf_tcap_tid, NULL);
PROTO_ITEM_SET_HIDDEN(actx->created_item);
offset = dissect_ber_octet_string(implicit_tag, actx, subtree, tvb, offset, hf_tcap_dtid,
                                    &parameter_tvb);

if (parameter_tvb){
	len = tvb_length_remaining(parameter_tvb, 0);
	switch(len) {
	case 1:
		gp_tcapsrt_info->dst_tid=tvb_get_guint8(parameter_tvb, 0);
		break;
	case 2:
		gp_tcapsrt_info->dst_tid=tvb_get_ntohs(parameter_tvb, 0);
		break;
	case 4:
		gp_tcapsrt_info->dst_tid=tvb_get_ntohl(parameter_tvb, 0);
		break;
	default:
		gp_tcapsrt_info->dst_tid=0;
		break;
	}

	if (len){
		col_append_str(actx->pinfo->cinfo, COL_INFO, "dtid(");
		for(i=0;i<len;i++)
			col_append_fstr(actx->pinfo->cinfo, COL_INFO, "%02x",tvb_get_guint8(parameter_tvb,i));
		col_append_str(actx->pinfo->cinfo, COL_INFO, ") ");
	}
}


  return offset;
}
