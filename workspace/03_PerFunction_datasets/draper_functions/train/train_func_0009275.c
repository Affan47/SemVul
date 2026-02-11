sieve_register_vacation(sieve_interp_t *interp, sieve_vacation_t *v)
{
    if (!interp->getenvelope) {
	return SIEVE_NOT_FINALIZED;
    }

    if (v->min_response == 0) v->min_response = 3;
    if (v->max_response == 0) v->max_response = 90;
    if (v->min_response < 0 || v->max_response < 7 || !v->autorespond
	|| !v->send_response) {
	return SIEVE_FAIL;
    }

    interp->vacation = v;
    return SIEVE_OK;
}
