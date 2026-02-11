wasp_proc_loop( ){
    if( wasp_proc_xp ){


        wasp_interp_xp = NULL;

        if( wasp_active_process ){
            wasp_active_process->deactivate( (wasp_object) wasp_active_process,
                                              wasp_active_process->context );
        }

        longjmp( *wasp_proc_xp, 101 );
    }

    jmp_buf exit;
    wasp_proc_xp = &exit;
    setjmp( exit );

    while( wasp_first_enabled ){
        wasp_active_process = wasp_first_enabled;
        while( wasp_active_process ){
            wasp_active_process->activate( (wasp_object) wasp_active_process,
                                           wasp_active_process->context );
            wasp_active_process->deactivate( (wasp_object) wasp_active_process,
                                             wasp_active_process->context );
            wasp_active_process = wasp_active_process->next;
        }
        wasp_sleep_if_idle( );
    }

    wasp_proc_xp = NULL;
}
