dissect_t124_DomainMCSPDU(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 193 "../../asn1/t124/t124.cnf"
  	gint domainmcs_value;

  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_t124_DomainMCSPDU, DomainMCSPDU_choice,
                                 &domainmcs_value);

	switch(domainmcs_value) {
	case 25:
	case 26:
	case 27:
	case 28:

		break;
	default:
		col_prepend_fstr(actx->pinfo->cinfo, COL_INFO, "%s ", val_to_str(domainmcs_value, t124_DomainMCSPDU_vals, "Unknown"));
		break;
	}


  return offset;
}
