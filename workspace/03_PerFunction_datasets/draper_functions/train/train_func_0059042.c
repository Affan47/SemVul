wasp_format_context( wasp_string buf, wasp_list context  ){
    if( context == NULL )return 0;

    if( wasp_format_context( buf, wasp_list_fv( wasp_cdr( context ) ) ) ){
        wasp_string_append_indent( buf, 11 );
    }else{
        wasp_string_append_cs( buf, "TRACEBACK: " );
    };

    wasp_format_value( buf, wasp_car( context ), 32, 3 );
    wasp_string_append_newline( buf );

    return 1;
}
