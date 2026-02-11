sha_pw_cmp (const char *userpwd, const char *dbpwd, unsigned int shaLen )
{


    int result = 1;
    char userhash[MAX_SHA_HASH_SIZE];
    char quick_dbhash[MAX_SHA_HASH_SIZE + SHA_SALT_LENGTH + 3];
    char *dbhash = quick_dbhash;
    struct berval salt;
    int hash_len;
    unsigned int secOID;
    char *schemeName;
    char *hashresult = NULL;
    PRUint32 dbpwd_len;


    switch (shaLen) {
        case SHA1_LENGTH:
            schemeName = SHA1_SCHEME_NAME;
            secOID = SEC_OID_SHA1;
            break;
        case SHA256_LENGTH:
            schemeName = SHA256_SCHEME_NAME;
            secOID = SEC_OID_SHA256;
            break;
        case SHA384_LENGTH:
            schemeName = SHA384_SCHEME_NAME;
            secOID = SEC_OID_SHA384;
            break;
        case SHA512_LENGTH:
            schemeName = SHA512_SCHEME_NAME;
            secOID = SEC_OID_SHA512;
            break;
        default:

            goto loser;
    }


    dbpwd_len = strlen(dbpwd);
    if ((dbpwd_len > 0) && (dbpwd[dbpwd_len-1] == '\n')) {
        dbpwd_len--;
    }


    hash_len = pwdstorage_base64_decode_len(dbpwd, dbpwd_len);
    if ( hash_len > sizeof(quick_dbhash) ) {
        dbhash = (char*) slapi_ch_calloc( hash_len, sizeof(char) );
        if ( dbhash == NULL ) goto loser;
    } else {
        memset( quick_dbhash, 0, sizeof(quick_dbhash) );
    }
    hashresult = PL_Base64Decode( dbpwd, dbpwd_len, dbhash );
    if (NULL == hashresult) {
        slapi_log_error( SLAPI_LOG_PLUGIN, plugin_name, hasherrmsg, schemeName, dbpwd );
        goto loser;
    } else if ( hash_len >= shaLen ) {
        salt.bv_val = (void*)(dbhash + shaLen);
        salt.bv_len = hash_len - shaLen;
    } else if ( hash_len >= DS40B1_SALTED_SHA_LENGTH ) {
        salt.bv_val = (void*)dbhash;
        salt.bv_len = OLD_SALT_LENGTH;
    } else {
                slapi_log_error( SLAPI_LOG_PLUGIN, plugin_name, hasherrmsg, schemeName, dbpwd );
        goto loser;
    }


    memset( userhash, 0, sizeof(userhash) );
    if ( sha_salted_hash( userhash, userpwd, &salt, secOID ) != SECSuccess ) {
                slapi_log_error( SLAPI_LOG_PLUGIN, plugin_name, "sha_pw_cmp: sha_salted_hash() failed\n");
        goto loser;
    }


    result = ( hash_len >= shaLen ) ?
        ( memcmp( userhash, dbhash, shaLen ) ) :
        ( memcmp( userhash, dbhash + OLD_SALT_LENGTH,
                  hash_len - OLD_SALT_LENGTH ) );

    loser:
    if ( dbhash && dbhash != quick_dbhash ) slapi_ch_free_string( &dbhash );
    return result;
}
