sasl_client_done(void)
{
    int result = SASL_CONTINUE;

    if (_sasl_server_cleanup_hook == NULL && _sasl_client_cleanup_hook == NULL) {
	return SASL_NOTINIT;
    }

    if (_sasl_client_cleanup_hook) {
	result = _sasl_client_cleanup_hook();

	if (result == SASL_OK) {
	    _sasl_client_idle_hook = NULL;
	    _sasl_client_cleanup_hook = NULL;
	} else {
	    return result;
	}
    }

    if (_sasl_server_cleanup_hook || _sasl_client_cleanup_hook) {
	return result;
    }

    sasl_common_done();

    return SASL_OK;
}
