smime_mapi_by_cipher (unsigned long cipher)
{
    int i;

    for (i = 0; i < smime_symmetric_count; i++) {
	if (smime_cipher_maps[i].cipher == cipher)
	    break;
    }

    if (i == smime_symmetric_count)
	return -1;

    return i;
}
