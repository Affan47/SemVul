wasp_string_alter(
    wasp_string string, wasp_integer dstofs, wasp_integer dstlen,
    const void* src, wasp_integer srclen
){


    AUDIT_STRING( string );
    wasp_integer newlen = string->length + srclen - dstlen;

    wasp_string_expand( string, newlen );

    void* dst = string->pool + string->origin + dstofs;

    void* tail = dst + dstlen;
    wasp_integer taillen = string->length - dstlen - dstofs;

    void* newtail = dst + srclen;

    if( taillen && ( tail != newtail ))memmove( dst + srclen, tail, taillen );
    if( srclen ) memmove( dst, src, srclen );

    string->length = newlen;
    string->pool[ string->origin + newlen ] = 0;
    AUDIT_STRING( string );
}
