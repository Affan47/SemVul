OS_FreeTLSIndex(OS_TLSIndex nIndex)
{
	if (nIndex == OS_INVALID_TLS_INDEX) {
		assert(0 && "OS_SetTLSValue(): Invalid TLS Index");
		return false;
	}


	if (pthread_key_delete(nIndex) == 0)
		return true;
	else
		return false;
}
