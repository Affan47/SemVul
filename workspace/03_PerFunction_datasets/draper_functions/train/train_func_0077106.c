wasp_instr_usen( ){
    wasp_word max = wasp_imm_fv( WASP_AX ) + 1;

    if( WASP_CP->count < max ){
        wasp_errf( wasp_es_vm, "sii", "argument underflow", WASP_CP->count, max );
    }else if( WASP_CP->count > max ){
        wasp_errf( wasp_es_vm, "sii", "argument overflow", WASP_CP->count, max );
    };


    wasp_vector env = wasp_make_vector( wasp_imm_fv( WASP_BX ) );


    wasp_word ix = 0;

    wasp_pair p = wasp_list_fv( wasp_cdr( WASP_CP->head ) );

    while( p ){
        wasp_vector_put( env, ix, wasp_car( p ) );
        p = wasp_list_fv( wasp_cdr( p ) );
        ix ++;
    }


    WASP_EP = wasp_cons( wasp_vf_vector( env ), wasp_vf_list( WASP_EP ) );


    wasp_next_instr( );
}
