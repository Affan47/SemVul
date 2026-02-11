eaptls_process(EAP_HANDLER *handler)
{
	tls_session_t *tls_session = (tls_session_t *) handler->opaque;
	EAPTLS_PACKET	*tlspacket;
	fr_tls_status_t	status;
	REQUEST *request = handler->request;

	if (!request) return FR_TLS_FAIL;

	RDEBUG2("processing EAP-TLS");
	SSL_set_ex_data(tls_session->ssl, FR_TLS_EX_INDEX_REQUEST, request);

	if (handler->certs) pairadd(&request->packet->vps,
				    paircopy(handler->certs));


	status = eaptls_verify(handler);
	RDEBUG2("eaptls_verify returned %d\n", status);

	switch (status) {
	default:
	case FR_TLS_INVALID:
	case FR_TLS_FAIL:


	case FR_TLS_SUCCESS:
		goto done;


	case FR_TLS_REQUEST:
		eaptls_request(handler->eap_ds, tls_session);
		status = FR_TLS_HANDLED;
		goto done;


	case FR_TLS_OK:
		RDEBUG2("Done initial handshake");


	case FR_TLS_FIRST_FRAGMENT:
	case FR_TLS_MORE_FRAGMENTS:
	case FR_TLS_LENGTH_INCLUDED:
	case FR_TLS_MORE_FRAGMENTS_WITH_LENGTH:
		break;
	}


	if ((tlspacket = eaptls_extract(request, handler->eap_ds, status)) == NULL) {
		status = FR_TLS_FAIL;
		goto done;
	}


	if (tlspacket->dlen !=
	    (tls_session->record_plus)(&tls_session->dirty_in, tlspacket->data, tlspacket->dlen)) {
		eaptls_free(&tlspacket);
		RDEBUG("Exceeded maximum record size");
		status =FR_TLS_FAIL;
		goto done;
	}


	eaptls_free(&tlspacket);


	if (SSL_is_init_finished(tls_session->ssl)) {


	        if ((status == FR_TLS_MORE_FRAGMENTS) ||
        	    (status == FR_TLS_MORE_FRAGMENTS_WITH_LENGTH) ||
            	    (status == FR_TLS_FIRST_FRAGMENT)) {


			eaptls_send_ack(handler->eap_ds,
					tls_session->peap_flag);
			RDEBUG2("Init is done, but tunneled data is fragmented");
			status = FR_TLS_HANDLED;
			goto done;
		}

		status = tls_application_data(tls_session, request);
		goto done;
	}


	status = eaptls_operation(status, handler);

 done:
	SSL_set_ex_data(tls_session->ssl, FR_TLS_EX_INDEX_REQUEST, NULL);

	return status;
}
