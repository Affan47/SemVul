wasp_isa( wasp_value x, wasp_value t ){
    if( wasp_is_type( t ) ){
        return wasp_is_subtype( wasp_value_type( x ), wasp_type_fv( t ) );
    }else if( wasp_is_cell( x ) && wasp_is_tag( t ) ){
        return wasp_cell_fv( x )->tag == wasp_tag_fv( t );
    }else{
        return 0;
    }
}
