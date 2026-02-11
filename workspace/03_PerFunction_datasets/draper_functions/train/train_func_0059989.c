wasp_string_append_exprs( wasp_string str, wasp_list list ){
    if( list == NULL ) return;
    wasp_pair p = list;

    for(;;){
        wasp_string_append_expr( str, wasp_car( p ) );
        wasp_string_append_newline( str );

        wasp_value v = wasp_cdr( p );
        if( wasp_is_pair( v ) ){
            p = wasp_pair_fv( v );
        }else if( wasp_is_null( v ) ){
            return;
        }else{
            wasp_errf( wasp_es_vm, "sxx", "last pair cdr is not null", list, v );
        }
    };
}
