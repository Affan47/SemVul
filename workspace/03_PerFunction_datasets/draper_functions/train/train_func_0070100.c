asn1c_print_streams(arg_t *arg)  {
	compiler_streams_t *cs = arg->expr->data;
	asn1p_expr_t *expr = arg->expr;
	int i;

	for(i = 1; i < OT_MAX; i++) {
		out_chunk_t *ot;
		if(TQ_FIRST(&cs->destination[i].chunks) == NULL)
			continue;

		printf("\n/*** <<< %s [%s] >>> ***/\n\n",
			_compiler_stream2str[i],
			expr->Identifier);

		TQ_FOR(ot, &(cs->destination[i].chunks), next) {
			fwrite(ot->buf, ot->len, 1, stdout);
		}
	}

	return 0;
}
