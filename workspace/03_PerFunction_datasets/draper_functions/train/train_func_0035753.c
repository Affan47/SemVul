readany(FILE * file, char * buffer, fortint * prod_len)


{


fortint length;
fortint original_len;

    original_len = *prod_len;
    length =  readprod(NULL,buffer,&original_len,fileRead,fileSeek,fileTell,
                       file);
    *prod_len = original_len;

    if ( buffer == NULL )
        return ( length == -1 ? length : -3 );
    else
        return ( length > 0 ? 0 : length );

}
