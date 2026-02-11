VFY_Update(VFYContext *cx, const unsigned char *input, unsigned inputLen)
{
    if (cx->hashcx == NULL) {
	PORT_SetError(SEC_ERROR_INVALID_ARGS);
	return SECFailure;
    }
    (*cx->hashobj->update)(cx->hashcx, input, inputLen);
    return SECSuccess;
}
