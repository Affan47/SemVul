makeGlobalSalt(NSSLOWKEYDBHandle *handle)
{
    DBT saltKey;
    DBT saltData;
    unsigned char saltbuf[16];
    int status;

    saltKey.data = SALT_STRING;
    saltKey.size = sizeof(SALT_STRING) - 1;

    saltData.data = (void *)saltbuf;
    saltData.size = sizeof(saltbuf);
    RNG_GenerateGlobalRandomBytes(saltbuf, sizeof(saltbuf));


    status = keydb_Put(handle, &saltKey, &saltData, 0);
    if ( status ) {
	return(SECFailure);
    }

    return(SECSuccess);
}
