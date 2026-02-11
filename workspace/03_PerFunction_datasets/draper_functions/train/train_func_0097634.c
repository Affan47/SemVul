bson_append_binary( bson_buffer * b, const char * name, char type, const char * str, int len ){
    if ( ! bson_append_estart( b , bson_bindata , name , 4+1+len ) ) return 0;
    bson_append32(b, &len);
    bson_append_byte(b, type);
    bson_append(b, str, len);
    return b;
}
