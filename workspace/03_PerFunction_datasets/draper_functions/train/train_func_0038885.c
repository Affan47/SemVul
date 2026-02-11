wasp_parse_sym( char** r_str, wasp_boolean* r_succ ){
    char* str = *r_str;
    char* sym = str;

    char ch = *str;
    int any = 0;

    for(;;)switch( *str ){
    case ';':
    case '.':
    case ')':
    case ' ':
    case '\r':
    case '\n':
    case '\t':
    case '\0':
        goto done;
    default:
        if( ! isprint( ch ) ) goto done;
        any = 1;
        str++;
    }
done:
    *r_succ = any;
    *r_str = str;
    if( any ){
        return wasp_symbol_fm( sym, str - sym );
    }else{
        wasp_parse_errmsg = "expected symbol";
        wasp_parse_incomplete = 1;
        return NULL;
    }
}
