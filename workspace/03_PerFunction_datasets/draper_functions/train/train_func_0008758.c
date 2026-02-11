wait_for_status( int fd, int itf, Msgs *msgs ){
	Message *m = NULL;
	VarBind *varbind;
	VarBindList *vbl;

	m = wait_for_response( fd, itf, msgs, RESPONSE_TIMEOUT );
	if( m == NULL ) return NULL;

	while( RESP_RID( m ) != GETNEXT_RID( msgs->addrtable )){
		m = wait_for_response( fd, itf, msgs, RESPONSE_TIMEOUT );
		if( m == NULL ) return NULL;
	}


	vbl = m->data->a.get_response->variable_bindings;
	FOR_EACH_LIST_ELMT(varbind, vbl) {
		if (AsnOidCompare(&atmfSrvcRegATMAddress,
					&varbind->name) == AsnOidRoot) {
			add_lecs(itf, varbind->value->a.simple->a.string->octs);
		} else if (AsnOidCompare(&atmfAddressStatus,
					&varbind->name) == AsnOidRoot) {
			diag(COMPONENT, DIAG_ERROR,
				"address already registered in switch");
		}
	}

	return m;
}
