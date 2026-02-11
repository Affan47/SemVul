dissect_t124_T_userData_01(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 179 "../../asn1/t124/t124.cnf"
    tvbuff_t	*next_tvb = NULL;

  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, &next_tvb);


	if(next_tvb) {

	     dissector_try_uint(t124_sd_dissector_table, channelId, next_tvb, actx->pinfo, top_tree);

	}


  return offset;
}
