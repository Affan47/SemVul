u_parseString(const char *s,
              UChar *dest, int32_t destCapacity,
              uint32_t *pFirst,
              UErrorCode *pErrorCode) {
    char *end;
    uint32_t value;
    int32_t destLength;

    if(pErrorCode==NULL || U_FAILURE(*pErrorCode)) {
        return 0;
    }
    if(s==NULL || destCapacity<0 || (destCapacity>0 && dest==NULL)) {
        *pErrorCode=U_ILLEGAL_ARGUMENT_ERROR;
    }

    if(pFirst!=NULL) {
        *pFirst=0xffffffff;
    }

    destLength=0;
    for(;;) {
        s=u_skipWhitespace(s);
        if(*s==';' || *s==0) {
            if(destLength<destCapacity) {
                dest[destLength]=0;
            } else if(destLength==destCapacity) {
                *pErrorCode=U_STRING_NOT_TERMINATED_WARNING;
            } else {
                *pErrorCode=U_BUFFER_OVERFLOW_ERROR;
            }
            return destLength;
        }


        value=(uint32_t)uprv_strtoul(s, &end, 16);
        if(end<=s || (*end!=' ' && *end!='\t' && *end!=';' && *end!=0) || value>=0x110000) {
            *pErrorCode=U_PARSE_ERROR;
            return 0;
        }


        if(destLength==0 && pFirst!=NULL) {
            *pFirst=value;
        }


        if((destLength+UTF_CHAR_LENGTH(value))<=destCapacity) {
            UTF_APPEND_CHAR_UNSAFE(dest, destLength, value);
        } else {
            destLength+=UTF_CHAR_LENGTH(value);
        }


        s=end;
    }
}
