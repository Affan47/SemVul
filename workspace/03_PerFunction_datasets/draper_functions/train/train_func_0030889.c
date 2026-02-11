ck_add_ugen_func( Chuck_DL_Query * query, f_tick ugen_tick, f_pmsg ugen_pmsg )
{

    if( !query->curr_class )
    {

        EM_error2( 0, "class import: add_ugen_func invoked without begin_class..." );
        return;
    }


    if( query->curr_class->ugen_tick && ugen_tick )
    {

        EM_error2( 0, "class import: ugen_tick already defined..." );
        return;
    }


    if( query->curr_class->ugen_pmsg && ugen_pmsg )
    {

        EM_error2( 0, "class import: ugen_pmsg already defined..." );
        return;
    }


    if( ugen_tick ) query->curr_class->ugen_tick = ugen_tick;
    if( ugen_pmsg ) query->curr_class->ugen_pmsg = ugen_pmsg;
    query->curr_func = NULL;
}
