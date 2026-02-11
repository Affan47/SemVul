mongo_pass_digest( mongo *conn, const char *user, const char *pass, char hex_digest[33] ) {
    mongo_md5_state_t st;
    mongo_md5_byte_t digest[16];

    if( strlen( user ) >= INT32_MAX || strlen( pass ) >= INT32_MAX ) {
        conn->err = MONGO_BSON_TOO_LARGE;
        return MONGO_ERROR;
    }
    mongo_md5_init( &st );
    mongo_md5_append( &st, ( const mongo_md5_byte_t * )user, ( int )strlen( user ) );
    mongo_md5_append( &st, ( const mongo_md5_byte_t * )":mongo:", 7 );
    mongo_md5_append( &st, ( const mongo_md5_byte_t * )pass, ( int )strlen( pass ) );
    mongo_md5_finish( &st, digest );
    digest2hex( digest, hex_digest );

    return MONGO_OK;
}
