wasp_timeout_mt( wasp_task task ){
    wasp_input input = wasp_input_fv( task->context );

    if( wasp_input_monitored( input ) ){
        wasp_wake_monitor( input, wasp_vf_symbol( wasp_ss_timeout ) );
    };

    return 0;
}
