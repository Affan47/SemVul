wasp_parse_dec( char** r_str, wasp_boolean* r_succ ){
    char* str = *r_str;
    wasp_quad result = 0;
    wasp_boolean any = 0;

    for(;;){
        char ch = *str;

        if(( ch >= '0' )&&( ch <= '9' )){
            result = result * 10 + ( ch - '0' );
        }else{
            break;
        }

        str++;
        any = 1;
    };

    if( any ){
        *r_succ = 1;
        *r_str = str;
    }else{
        wasp_parse_errmsg = wasp_em_nodigits;
        wasp_parse_incomplete = 1;
        *r_succ = 0;
    }

    return result;
}
