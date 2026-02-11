__mongo_set_error( mongo *conn, mongo_error_t err, const char *str,
                                     int errcode ) {
    size_t str_size = 1;
    conn->err = err;
    conn->errcode = errcode;
    if( str ) {
        str_size = strlen( str ) + 1;
        if (str_size > MONGO_ERR_LEN) str_size = MONGO_ERR_LEN;
        memcpy( conn->errstr, str, str_size );
    }
    conn->errstr[str_size-1] = '\0';
}
