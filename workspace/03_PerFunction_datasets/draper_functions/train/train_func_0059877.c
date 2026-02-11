xlsx_validation_expr (GsfXMLIn *xin, G_GNUC_UNUSED GsfXMLBlob *blob)
{
	XLSXReadState *state = (XLSXReadState *)xin->user_state;
	GnmParsePos pp;
	GnmExprTop const *texpr;

	if (state->validation == NULL)
		return;


	parse_pos_init (&pp, NULL, state->sheet,
		state->pos.col, state->pos.row);
	texpr = xlsx_parse_expr (xin, xin->content->str, &pp);
	if (NULL != texpr) {
		gnm_validation_set_expr (state->validation, texpr,
			xin->node->user_data.v_int);
		gnm_expr_top_unref (texpr);
	}
}
